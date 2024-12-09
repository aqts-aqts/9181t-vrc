#pragma once
#ifndef drive_h
#define drive_h

#define DEADZONE 5
#define ACTIVE_BRAKE_KP 0

#define LEFT_CURVE_SCALE 0
#define RIGHT_CURVE_SCALE 2.1

#define WHEEL_DIAMETER 3.25
#define DRIVE_CARTRIDGE_RPM 600
#define DRIVE_RATIO 1.6667 // 60:36

#define CLAMP_COOLDOWN 600
#define WALL_STAKE_COOLDOWN 600

#define WALL_STAKE_RPM 100

#define INTAKE_VOLTS 127
#define DOINKER_VOLTS 80

#include "main.h"
namespace global {
    extern void drive();
    extern double apply_threshold(double input);

    extern double curve_left(double input);
    extern double curve_right(double input);
    
    extern double get_drive_tick_per_inch();
    extern double get_left_drive_sensor();
    extern double get_right_drive_sensor();
}
#endif