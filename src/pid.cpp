#include "main.h"
#include "include/global.h"

using namespace global;

double l_move_start = 0;
double r_move_start = 0;
double turn_move_start = 0;

namespace global {
    double left_error = 0;
    double right_error = 0;
    double prev_left_error = 0;
    double prev_right_error = 0;
    double turn_error = 0;
    double prev_turn_error = 0;
    double turn_total_error = 0;
    double left_power = 0;
    double right_power = 0;
    double turn_power = 0;
    double max_power = 0;
    double left_target = NAN;
    double right_target = NAN;
    double imu_target = NAN;
    double inital_rotation = NAN;
    double rotation_error = 0;

    double right_error_timeout = 0;
    double right_error_start = NAN;

    double left_error_timeout = 0;
    double left_error_start = NAN;

    double turn_error_timeout = 0;
    double turn_error_start = NAN;

    double turn_kP = tkP;
    double turn_kD = tkD;
    double turn_kI = tkI;

    double left_drive_kP = kP;
    double left_drive_kD = kD;
    double right_drive_kP = kP;
    double right_drive_kD = kD;

    double left_timeout = 1500;
    double right_timeout = 1500;
    double turn_timeout = 1500;

    void set_drive_target(double distance, double power, double timeout, double p, double d, double rp, double rd) {
        left_drive_kP = p;
        left_drive_kD = d;
        right_drive_kP = rp;
        right_drive_kD = rd;
        distance *= 360 / (wheel_diameter * M_PI);
        left_target = left_drive.get_position() + distance;
        right_target = right_drive.get_position() + distance;
        max_power = std::fabs(power);
        inital_rotation = (imu1.get_rotation() + imu2.get_rotation()) / 2;
        l_move_start = pros::millis();
        r_move_start = pros::millis();
        left_timeout = timeout;
        right_timeout = timeout;
    }

    void set_turn_target(double angle, double power, double timeout, double p, double d, double i) {
        turn_kP = p;
        turn_kD = d;
        turn_kI = i;
        imu_target = angle;
        max_power = power;
        turn_move_start = pros::millis();
        turn_timeout = timeout;
    }

    void move_to(double target_x, double target_y, double max_power) {
        double target_distance = sqrt(pow(target_x - x, 2) + pow(target_y - y, 2));
        set_drive_target(target_distance, max_power);
    }

    void turn_to_face(double target_x, double target_y, double max_power) {
        double target_angle = atan2(target_y - y, target_x - x) * (180.0 / M_PI);
        set_turn_target(target_angle, max_power);
    }

    void set_drive_power(double left_power, double right_power) {
        left_drive.move(left_power);
        right_drive.move(right_power);
    }

    void left_pid_loop() {
        if (std::isnan(left_target) || !std::isnan(imu_target)) // turning takes priority
            return;

        left_error = left_target - left_drive.get_position();
        left_power = left_error * left_drive_kP + (left_error - prev_left_error) * left_drive_kD;
        left_power = std::clamp(left_power, -max_power, max_power);
        left_power += rotation_error * heading_kP;
        left_drive.move(left_power);
        prev_left_error = left_error;

        if (std::fabs(left_error) < 20 || pros::millis() - l_move_start > left_timeout) {// 20 ticks of error
            left_error_start = (std::isnan(left_error_start)) ? pros::millis(): left_error_start;
            if (pros::millis() - left_error_start > left_error_timeout || pros::millis() - l_move_start > left_timeout) {
                left_target = NAN;
                set_drive_power(0, 0);
            }
        } else {
            left_error_start = NAN;
        }
    }

    void right_pid_loop() {
        if (std::isnan(right_target) || !std::isnan(imu_target)) // turning takes priority
            return;
        
        right_error = right_target - right_drive.get_position();
        right_power = right_error * right_drive_kP + (right_error - prev_right_error) * right_drive_kD;
        right_power = std::clamp(right_power, -max_power, max_power);
        right_power -= rotation_error * heading_kP;
        right_drive.move(right_power);
        prev_right_error = right_error;

        if (std::fabs(right_error) < 20 || pros::millis() - r_move_start > right_timeout) {// 20 ticks of error
            right_error_start = (std::isnan(right_error_start)) ? pros::millis(): right_error_start;
            if (pros::millis() - right_error_start > right_error_timeout || pros::millis() - r_move_start > right_timeout) {
                right_target = NAN;
                set_drive_power(0, 0);
            }
        } else {
            right_error_start = NAN;
        }
    }

    void imu_pid_loop() {
        if (std::isnan(imu_target))
            return;
        
        turn_error = imu_target - current_heading;
        turn_total_error += turn_error;
        turn_power = turn_error * turn_kP + (turn_error - prev_turn_error) * turn_kD + turn_total_error * turn_kI;
        turn_power = std::clamp(turn_power, -max_power, max_power);
        left_drive.move(turn_power);
        right_drive.move(-turn_power);
        prev_turn_error = turn_error;

        if (std::fabs(turn_error) < 2 || pros::millis() - turn_move_start > turn_timeout) {// 2 degrees of error
            turn_error_start = (std::isnan(turn_error_start)) ? pros::millis(): turn_error_start;
            if (pros::millis() - turn_error_start > turn_error_timeout || pros::millis() - turn_move_start > turn_timeout) {
                imu_target = NAN;
                set_drive_power(0, 0);
            }
        } else {
            turn_error_start = NAN;
        }
    }

    void wait_pid() {
        while (!std::isnan(left_target) || !std::isnan(right_target) || !std::isnan(imu_target))
            pros::delay(10);
    }

    void wait_drive(double distance) {
        if (std::isnan(left_target) || std::isnan(right_target))
            return;
        distance *= 360 / (3.25 * M_PI);
        while ((std::fabs(left_drive.get_position() - left_target) + std::fabs(right_drive.get_position() - right_target)) / 2 < distance)
            pros::delay(10);
    }

    void wait_turn(double angle) {
        while (std::fabs(current_heading - imu_target) < angle)
            pros::delay(10);
    }

    void pid_thread() {
        while (true) {
            pros::screen::print(TEXT_MEDIUM, 1, "Left: %.2f, %.2f", left_error, left_target);
            pros::screen::print(TEXT_MEDIUM, 2, "Right: %.2f, %.2f", right_error, right_target);
            pros::screen::print(TEXT_MEDIUM, 3, "Turn: %.2f, %.2f", turn_error, imu_target);
            pros::screen::print(TEXT_MEDIUM, 4, "Heading: %.2f, %.2f", rotation_error, inital_rotation);
            if (!std::isnan(inital_rotation))
                rotation_error = (imu1.get_rotation() + imu2.get_rotation()) / 2 - inital_rotation;
            left_pid_loop();
            right_pid_loop();
            imu_pid_loop();
            pros::delay(10);
        }
    }
}