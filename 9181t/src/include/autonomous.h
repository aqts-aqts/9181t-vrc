#pragma once
#ifndef autonomous_h
#define autonomous_h

// pid constants
#define heading_kP 0

// odom constants
#define wheel_diameter 3.25
#define imu_drift 345 // the amount of degrees imu registers after a full turn
#define x_offset 0 // the perpendicular distance between x tracking wheel and tracking center
#define y_offset 0 // the perpendicular distance between y tracking wheel and tracking center

#define kP 0.3
#define kD 0
#define tkP 1.0
#define tkD 0.8
#define tkI 0.001

#include "main.h"
namespace global {
    // pid constants
    extern double left_error, right_error, prev_left_error, prev_right_error; // current and previous error for drive
    extern double turn_error, prev_turn_error, turn_total_error; // current and previous error for imu
    extern double max_power; // maximum power for drive
    extern double left_power, right_power; // left and right drive powers
    extern double turn_power; // turn power
    extern double left_target, right_target; // left and right drive targets
    extern double imu_target; // turn target
    extern double inital_rotation, rotation_error;

    extern double left_drive_kP, left_drive_kD, right_drive_kP, right_drive_kD;
    extern double turn_kP, turn_kD, turn_kI;

    // pid controls
    extern void set_drive_target(double distance, double power, double timeout = 1500, double p = kP, double d = kD, double rp = kP, double rd = kD);
    extern void set_turn_target(double angle, double power, double timeout = 1500, double p = tkP, double d = tkD, double i = tkI);
    extern void set_drive_power(double left_power, double right_power);
    extern void wait_pid(); // wait until drive or turn has reached target
    extern void wait_drive(double distance); // wait until drive has traveled a certain distance
    extern void wait_turn(double angle); // wait until turn has turned a certain angle
    extern void move_to(double target_x, double target_y, double max_power);
    extern void turn_to_face(double target_x, double target_y, double max_power);
    
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
    extern double current_heading;
    extern double current_heading_rad, prev_heading_rad, delta_heading_rad;
    extern double delta_x_tracking, delta_y_tracking; 
    extern double delta_x, delta_y;
    extern double actual_x_change, actual_y_change;

    // odom threads
    extern void odom_thread();
    extern void update_sensors();
    extern void position_tracking();

    // autons
    extern void auto1();
}
#endif