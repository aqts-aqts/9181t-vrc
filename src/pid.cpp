#include "main.h"

using namespace global;

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
    double current_angle = 0;

    double drive_error_timeout = 0;
    double left_error_start = NAN;
    double right_error_start = NAN;

    double turn_error_timeout = 0;
    double turn_error_start = NAN;

    double turn_kP = 0;
    double turn_kD = 0;
    double turn_kI = 0;
    double turn_start_i = 0;

    double left_drive_kP = 0;
    double left_drive_kD = 0;
    double right_drive_kP = 0;
    double right_drive_kD = 0;

    double drive_timeout = 0;
    double turn_timeout = 0;

    double drive_big_error = 0;
    double drive_small_error = 0;

    double turn_big_error = 0;
    double turn_small_error = 0;

    double left_move_start = 0;
    double right_move_start = 0;
    double turn_move_start = 0;

    // new stuff
    double drive_kP = 0;
    double drive_kD = 0;

    double drive_error = 0;
    double drive_power = 0;

    double prev_drive_error = 0;
    double drive_target = NAN;

    double drive_move_start = 0;
    double drive_error_start = 0;
    
    void set_drive_constants(double p, double d, double timeout, double big_error, double small_error, double error_timeout) {
        left_drive_kP = p;
        right_drive_kP = p;
        left_drive_kD = d;
        right_drive_kD = d;

        current_angle = current_rotation;

        drive_timeout = (timeout != -1) ? timeout: drive_timeout;
        drive_big_error = (big_error != -1) ? big_error: drive_big_error;
        drive_small_error = (small_error != -1) ? small_error: drive_small_error;
        drive_error_timeout = (error_timeout != -1) ? error_timeout: drive_error_timeout;
    }

    /*void set_drive_constants(double p, double d, double timeout, double big_error, double small_error, double error_timeout) {
        drive_kP = p;
        drive_kD = d;

        drive_timeout = (timeout != -1) ? timeout: drive_timeout;
        drive_big_error = (big_error != -1) ? big_error: drive_big_error;
        drive_small_error = (small_error != -1) ? small_error: drive_small_error;
        drive_error_timeout = (error_timeout != -1) ? error_timeout: drive_error_timeout;
    }*/

    void set_turn_constants(double p, double i, double d, double s_i, double timeout, double big_error, double small_error, double error_timeout) {
        turn_kP = p;
        turn_kI = i;
        turn_kD = d;
        turn_start_i = (s_i != -1) ? s_i: turn_start_i;

        turn_timeout = (timeout != -1) ? timeout: turn_timeout;
        turn_big_error = (big_error != -1) ? big_error: turn_big_error;
        turn_small_error = (small_error != -1) ? small_error: turn_small_error;
        turn_error_timeout = (error_timeout != -1) ? error_timeout: turn_error_timeout;
    }

    
    void set_drive_target(double distance, double power) {
        distance *= 360.0 / (wheel_diameter * M_PI);
        left_target = left_drive.get_position() + distance;
        right_target = right_drive.get_position() + distance;
        max_power = std::fabs(power);

        current_angle = (imu1.get_rotation() + imu2.get_rotation()) / 2;
        left_move_start = pros::millis();
        right_move_start = pros::millis();

        prev_left_error = left_target - left_drive.get_position();
        prev_right_error = right_target - right_drive.get_position();
    }

    /*void set_drive_target(double distance, double power) {
        distance *= 360.0 / (wheel_diameter * M_PI);
        left_drive.tare_position_all();
        right_drive.tare_position_all();
        drive_target = distance;
        max_power = std::fabs(power);

        current_angle = (imu1.get_rotation() + imu2.get_rotation()) / 2;
        drive_move_start = pros::millis();

        prev_drive_error = drive_target - ((left_drive.get_position() + right_drive.get_position()) / 2);
    }*/

    void set_turn_target(double angle, double power) {
        imu_target = angle;
        max_power = power;

        turn_move_start = pros::millis();
        prev_turn_error = angle - current_rotation;
    }

    void move_to(double target_x, double target_y, double max_power) {
        double target_distance = sqrt(pow(target_x - x, 2) + pow(target_y - y, 2));
        set_drive_target(target_distance, max_power);
    }

    void turn_to_face(double target_x, double target_y, double max_power) {
        double dx = target_x - x;
        double dy = target_y - y;
        
        if (dx == 0 && dy == 0)
            return;

        double angle = 270 - atan2(dy, dx) * 180 / M_PI;

        while (angle - current_rotation > 180)
            angle -= 360;
        while (angle - current_rotation < -180)
            angle += 360;
    
        set_turn_target(angle, max_power);
    }

    void turn_to_face_back(double target_x, double target_y, double max_power) {
        double dx = target_x - x;
        double dy = target_y - y;
        double target_distance = sqrt(pow(dx, 2) + pow(dy, 2));
        double bearing_angle = fabs(atan(dy / target_distance) * 180 / M_PI);
        if (dy >= 0 && dx >= 0)
            bearing_angle = bearing_angle;
        else if (dy >= 0 && dx < 0)
            bearing_angle = 180 - bearing_angle;
        else if (dy < 0 && dx < 0)
            bearing_angle = 180 + bearing_angle;
        else
            bearing_angle = 360 - bearing_angle;

        double bearing_with_inertial = 270 - bearing_angle;
        double delta_heading = -floor((bearing_with_inertial - current_rotation + 180) / 360);
        double new_heading = bearing_with_inertial + delta_heading * 360;
    
        set_turn_target(new_heading, max_power);
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
        prev_left_error = left_error;

        if (std::fabs(left_error) < drive_big_error || pros::millis() - left_move_start > drive_timeout) { // 20 ticks of error
            left_error_start = (std::isnan(left_error_start)) ? pros::millis(): left_error_start;
            if (pros::millis() - left_error_start > drive_error_timeout || pros::millis() - left_move_start > drive_timeout) {
                left_target = NAN;
                left_error_start = NAN;
            } else if (std::fabs(left_error) < drive_small_error) {
                left_target = NAN;
                left_error_start = NAN;
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
        prev_right_error = right_error;

        if (std::fabs(right_error) < 20 || pros::millis() - right_move_start > drive_timeout) { // 20 ticks of error
            right_error_start = (std::isnan(right_error_start)) ? pros::millis(): right_error_start;
            if (pros::millis() - right_error_start > drive_error_timeout || pros::millis() - right_move_start > drive_timeout) {
                right_target = NAN;
                right_error_start = NAN;
            } else if (std::fabs(right_error) < drive_small_error) {
                right_target = NAN;
                right_error_start = NAN;
            }
        } else {
            right_error_start = NAN;
        }
    }

    /*void drive_pid_loop() {
        if (std::isnan(drive_target) || !std::isnan(imu_target)) // turning takes priority
            return;

        drive_error = drive_target - ((left_drive.get_position() + right_drive.get_position()) / 2);
        drive_power = drive_error * drive_kP + (drive_error - prev_drive_error) * drive_kD;
        drive_power = std::clamp(drive_power, -max_power, max_power);
        set_drive_power(left_power, right_power);
        prev_drive_error = drive_error;

        if (std::fabs(drive_error) < 20 || pros::millis() - drive_move_start > drive_timeout) { // 20 ticks of error
            drive_error_start = (std::isnan(drive_error_start)) ? pros::millis(): drive_error_start;
            if (pros::millis() - drive_error_start > drive_error_timeout || pros::millis() - drive_move_start > drive_timeout) {
                drive_target = NAN;
                drive_error_start = NAN;
                set_drive_power(0, 0);
            } else if (std::fabs(right_error) < drive_small_error) {
                drive_target = NAN;
                drive_error_start = NAN;
                set_drive_power(0, 0);
            }
        } else {
            drive_error_start = NAN;
        }
    }*/

    void imu_pid_loop() {
        if (std::isnan(imu_target))
            return;
        
        turn_error = imu_target - current_rotation;
        turn_total_error += ((fabs(turn_error) < turn_start_i) ? turn_error: 0);
        turn_power = turn_error * turn_kP + (turn_error - prev_turn_error) * turn_kD + ((fabs(turn_error) < turn_start_i) ? (turn_total_error * turn_kI): 0);
        turn_power = std::clamp(turn_power, -max_power, max_power);
        left_power = turn_power;
        right_power = -turn_power;
        prev_turn_error = turn_error;

        current_angle = current_rotation;

        if (std::fabs(turn_error) < turn_big_error || pros::millis() - turn_move_start > turn_timeout) {
            turn_error_start = (std::isnan(turn_error_start)) ? pros::millis(): turn_error_start;
            if (pros::millis() - turn_error_start > turn_error_timeout || pros::millis() - turn_move_start > turn_timeout) {
                imu_target = NAN;
                turn_error_start = NAN;
                turn_total_error = 0;
            } else if (std::fabs(turn_error) < turn_small_error) {
                imu_target = NAN;
                turn_error_start = NAN;
                turn_total_error = 0;
            }
        } else {
            turn_error_start = NAN;
        }
    }

    void heading_pid_loop() {
        if (!std::isnan(imu_target))
            return;

        left_power -= (current_rotation - current_angle) * heading_kP;
        right_power += (current_rotation - current_angle) * heading_kP;
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
        while (std::fabs(current_rotation - imu_target) < angle)
            pros::delay(10);
    }

    void pid_thread() {
        while (true) {
            pros::screen::print(TEXT_MEDIUM, 1, "Left: %.2f, %.2f", left_error, left_target);
            pros::screen::print(TEXT_MEDIUM, 2, "Right: %.2f, %.2f", right_error, right_target);
            pros::screen::print(TEXT_MEDIUM, 3, "Turn: %.2f, %.2f", turn_error, imu_target);
            pros::screen::print(TEXT_MEDIUM, 4, "Rotation: %.2f", current_rotation);
            pros::screen::print(TEXT_MEDIUM, 5, "Angle hold: %.2f", current_angle);

            left_power = 0;
            right_power = 0;

            left_pid_loop();
            right_pid_loop();
            imu_pid_loop();
            heading_pid_loop();

            set_drive_power(left_power, right_power);
            pros::delay(10);
        }
    }
}