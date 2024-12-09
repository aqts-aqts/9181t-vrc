#pragma once
#include "pros/adi.h"
#ifndef devices_h
#define devices_h

#include "main.h"
namespace global {
    // motors
    extern pros::Motor left_front;
    extern pros::Motor left_mid;
    extern pros::Motor left_back;
    extern pros::Motor right_front;
    extern pros::Motor right_mid;
    extern pros::Motor right_back;

    extern pros::Motor intake_front;
    extern pros::Motor intake_back;
    extern pros::Motor wall_stake_motor;

    // motor groups
    extern pros::MotorGroup left_drive;
    extern pros::MotorGroup right_drive;

    // controllers
    extern pros::Controller master;

    // sensors
    extern pros::Rotation horizontal_encoder;
    extern pros::Rotation vertical_encoder;

    extern pros::Rotation wall_stake_encoder;

    extern pros::IMU imu1;
    extern pros::IMU imu2;

    extern pros::adi::DigitalOut clamp1;
    extern pros::adi::DigitalOut clamp2;
}
#endif