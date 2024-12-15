#pragma once
#ifndef autonomous_h
#define autonomous_h

// pid constants
#define heading_kP 1

// odom constants
#define wheel_diameter 3.25
#define imu_drift 360 // the amount of degrees imu registers after a full turn
#define x_offset 3.2 // the perpendicular distance between x tracking wheel and tracking center
#define y_offset 0.8 // the perpendicular distance between y tracking wheel and tracking center
/*
for tuning: spin the robot clockwise, then use the formula: 
x_offset = ((degrees of x tracking wheel) / 360 * 2.75 * pi) / ((inertial heading degrees) / 180 * pi)
          = (x_tracking in inches) / (inertial in radians)
same for y_offset, but replace x with y
*/

namespace global {
    // pid constants
    extern double left_error, right_error, prev_left_error, prev_right_error; // current and previous error for drive
    extern double turn_error, prev_turn_error, turn_total_error; // current and previous error for imu
    extern double max_power; // maximum power for drive
    extern double left_power, right_power; // left and right drive powers
    extern double turn_power; // turn power
    extern double left_target, right_target; // left and right drive targets
    extern double imu_target; // turn target
    extern double current_angle;

    extern double left_drive_kP, left_drive_kD, right_drive_kP, right_drive_kD;
    extern double turn_kP, turn_kD, turn_kI;

    // pid controls
    extern void set_drive_constants(double p, double d, double timeout = -1, double big_error = -1, double small_error = -1, double error_timeout = -1);
    extern void set_turn_constants(double p, double i, double d, double s_i = -1, double timeout = -1, double big_error = -1, double small_error = -1, double error_timeout = -1);

    extern void set_drive_target(double distance, double power);
    extern void set_turn_target(double angle, double power);
    extern void set_drive_power(double left_power, double right_power);
    extern void wait_pid(); // wait until drive or turn has reached target
    extern void wait_drive(double distance); // wait until drive has traveled a certain distance
    extern void wait_turn(double angle); // wait until turn has turned a certain angle
    extern void move_to(double target_x, double target_y, double max_power);
    extern void move_to_back(double target_x, double target_y, double max_power);
    extern void turn_to_face(double target_x, double target_y, double max_power);
    extern void turn_to_face_back(double target_x, double target_y, double max_power);
    
    // pid threads
    extern void pid_thread();
    extern void left_pid_loop();
    extern void right_pid_loop();
    extern void imu_pid_loop();

    // odom constants
    extern double x, y; // current x and y position
    extern double x_tracking, y_tracking; // current x and y tracking wheel positions
    extern double prev_x, prev_y; // previous x and y position
    extern double prev_x_tracking, prev_y_tracking; // previous x and y tracking wheel positions
    extern double current_rotation;
    extern double current_rotation_rad, prev_rotation_rad, delta_rotation_rad;
    extern double delta_x_tracking, delta_y_tracking; 
    extern double delta_x, delta_y;
    extern double actual_x_change, actual_y_change;

    // odom threads
    extern void odom_thread();
    extern void update_sensors();
    extern void position_tracking();
}
#endif