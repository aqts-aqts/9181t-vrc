#include "main.h"
using namespace global;

namespace global {
    std::vector<std::vector<std::pair<double, double>>> paths = {};

    double max_velocity = 127.0;
    double k_turn = 0.5; // Adjust this for smoother turns
    double slew_rate = 5.0; // Velocity slew rate

    std::pair<double, double> find_lookahead_point(double x, double y, int path_index) {
        std::vector<std::pair<double, double>> waypoints = paths[path_index];
        double min_distance = std::numeric_limits<double>::max();
        std::pair<double, double> lookahead_point;

        for (const auto& point : waypoints) {
            double distance = std::sqrt(std::pow(point.first - x, 2) + std::pow(point.second - y, 2));
            if (std::fabs(distance - lookahead_distance) < min_distance) {
                min_distance = std::fabs(distance - lookahead_distance);
                lookahead_point = point;
            }
        }
        return lookahead_point;
    }

    double calculate_curvature(double x, double y, double heading, std::pair<double, double> lookahead_point) {
        double dx = lookahead_point.first - x;
        double dy = lookahead_point.second - y;

        double local_x = dx * std::cos(-heading) - dy * std::sin(-heading);
        double local_y = dx * std::sin(-heading) + dy * std::cos(-heading);

        if (local_x <= 0) return 0.0; // Lookahead point behind the robot

        return (2 * local_y) / (std::pow(local_x, 2) + std::pow(local_y, 2));
    }

    double slew(double target, double current, double rate) {
        if (std::fabs(target - current) > rate) {
            return current + rate * ((target > current) ? 1 : -1);
        }
        return target;
    }

    void follow_path(int path_index, double max_vel, bool async) {
        max_velocity = max_vel;
        double prev_velocity = 0.0;

        auto task_function = [&]() {
            while (true) {
                // Find the lookahead point
                std::pair<double, double> lookahead_point = find_lookahead_point(x, y, path_index);

                // Calculate curvature
                double curvature = calculate_curvature(x, y, current_rotation_rad, lookahead_point);

                // Calculate target velocity with slew rate limiting
                double distance_to_goal = std::sqrt(std::pow(x - paths[path_index].back().first, 2) + std::pow(y - paths[path_index].back().second, 2));
                double target_velocity = std::min(max_velocity, distance_to_goal * follow_kp);
                double velocity = slew(target_velocity, prev_velocity, slew_rate);
                prev_velocity = velocity;

                // Calculate motor powers based on curvature
                double left_power = velocity * (2 + curvature * wheelbase) / 2;
                double right_power = velocity * (2 - curvature * wheelbase) / 2;

                // Scale motor powers to stay within limits
                double max_power = std::max(std::fabs(left_power), std::fabs(right_power));
                if (max_power > max_velocity) {
                    left_power = (left_power / max_power) * max_velocity;
                    right_power = (right_power / max_power) * max_velocity;
                }

                set_drive_power(left_power, right_power);

                // Check if robot is close to the final waypoint
                if (distance_to_goal < 1.0) {
                    set_drive_power(0, 0);
                    break;
                }

                // Debugging output
                printf("X: %f, Y: %f, Heading: %f, Curvature: %f\n", x, y, current_rotation_rad, curvature);
                printf("Distance left: %f, Velocity: %f\n", distance_to_goal, velocity);
                printf("Left Power: %f, Right Power: %f\n", left_power, right_power);

                pros::delay(10);
            }
        };

        if (async) {
            pros::Task follower_task(task_function);
        } else {
            task_function();
        }
    }
}
