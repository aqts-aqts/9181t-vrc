#include "include/device.h"
#include "main.h"
#include "pros/misc.h"
using namespace global;

namespace global {
    pros::Motor left_front(6, pros::v5::MotorGears::blue);
    pros::Motor left_mid(12, pros::v5::MotorGears::blue);
    pros::Motor left_back(-13, pros::v5::MotorGears::blue);
    pros::Motor right_front(-8, pros::v5::MotorGears::blue);
    pros::Motor right_mid(10, pros::v5::MotorGears::blue);
    pros::Motor right_back(-21, pros::v5::MotorGears::blue);

    pros::Motor intake_front(-7, pros::v5::MotorGears::green); // 5.5
    pros::Motor intake_back(19, pros::v5::MotorGears::green);
    pros::Motor wall_stake_motor(14, pros::v5::MotorGears::green); // 5.5

    pros::MotorGroup left_drive({6, 12, -13});
    pros::MotorGroup right_drive({-8, 10, -21});

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Rotation horizontal_encoder(15);
    pros::Rotation vertical_encoder(17);

    pros::Rotation wall_stake_encoder(3);

    pros::IMU imu1(9);
    pros::IMU imu2(20);

    pros::adi::DigitalOut clamp1(1);
    pros::adi::DigitalOut clamp2(8);
}