#include "main.h"
using namespace global;

namespace global {
    std::vector<std::vector<std::pair<double, double>>> paths = {};

    double max_velocity = 127.0;

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

    double calculate_steering_angle(double x, double y, double heading, int path_index) {
        auto [lookahead_x, lookahead_y] = find_lookahead_point(x, y, path_index);

        double dx = lookahead_x - x;
        double dy = lookahead_y - y;

        double local_x = dx * std::cos(-heading) - dy * std::sin(-heading);
        double local_y = dx * std::sin(-heading) + dy * std::cos(-heading);

        if (local_x <= 0) {
            return 0.0;
        }

        double curvature = 2 * local_y / (lookahead_distance * lookahead_distance);
        return std::atan(wheelbase * curvature);
    }

    void follow_path(int path_index, double max_vel, bool async) {
        max_velocity = max_vel;

        auto task_function = [&]() {
            while (true) {
                double steering_angle = calculate_steering_angle(x, y, current_rotation_rad, path_index);
                std::vector<std::pair<double, double>> waypoints = paths[path_index];

                double velocity = std::min(max_velocity, std::sqrt(std::pow(waypoints.back().first - x, 2) + std::pow(waypoints.back().second - y, 2)) * follow_kp);
                double left_power = velocity - (steering_angle * velocity);
                double right_power = velocity + (steering_angle * velocity);

                set_drive_power(left_power, right_power);
                if (std::sqrt(std::pow(x - waypoints.back().first, 2) + std::pow(y - waypoints.back().second, 2)) < 1.0) {
                    set_drive_power(0, 0);
                    break;
                }

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