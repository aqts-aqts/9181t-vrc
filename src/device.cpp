#include "main.h"
#include "pros/distance.hpp"
#include "pros/optical.hpp"
using namespace global;

namespace global {
    pros::Motor left_front(6, pros::v5::MotorGears::blue);
    pros::Motor left_mid(12, pros::v5::MotorGears::blue);
    pros::Motor left_back(-13, pros::v5::MotorGears::blue);
    pros::Motor right_front(-8, pros::v5::MotorGears::blue);
    pros::Motor right_mid(10, pros::v5::MotorGears::blue);
    pros::Motor right_back(-21, pros::v5::MotorGears::blue);

    pros::Motor intake_front(19, pros::v5::MotorGears::blue); // 5.5
    pros::Motor intake_back(-14, pros::v5::MotorGears::green);
    pros::Motor wall_stake_motor(5, pros::v5::MotorGears::green); // 5.5

    pros::MotorGroup left_drive({6, 12, -11});
    pros::MotorGroup right_drive({-8, 10, -21});

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Rotation horizontal_encoder(15);
    pros::Rotation vertical_encoder(17);

    pros::Rotation wall_stake_encoder(3);

    pros::IMU imu1(9);
    pros::IMU imu2(20);

    pros::adi::DigitalIn intake_limit(5);
    pros::adi::DigitalOut clamp(8);
    pros::adi::DigitalOut doinker(1);

    pros::Distance distance(16);
    pros::Optical colour(18);

    bool holding = true;
    int inital_angle = 297;
}