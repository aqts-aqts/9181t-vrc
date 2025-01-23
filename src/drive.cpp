#include "main.h"
using namespace global;

namespace global {
    double curve_left(double input) {
        if (LEFT_CURVE_SCALE == 0)
            return input;
        return (powf(2.718, -(LEFT_CURVE_SCALE / 10.0)) + powf(2.718, (fabs(input) - 127) / 10) * (1 - powf(2.718, -(LEFT_CURVE_SCALE / 10.0)))) * input;
    }

    double curve_right(double input) {
        if (RIGHT_CURVE_SCALE == 0)
            return input;
        return (powf(2.718, -(RIGHT_CURVE_SCALE / 10.0)) + powf(2.718, (fabs(input) - 127) / 10) * (1 - powf(2.718, -(RIGHT_CURVE_SCALE / 10.0)))) * input;
    }

    double get_drive_tick_per_inch() {
        const double circumference = wheel_diameter * M_PI;
        double tick_per_revolution = DRIVE_CARTRIDGE_RPM * DRIVE_RATIO;

        return tick_per_revolution / circumference;
    }

    double get_left_drive_raw() {
        std::vector<double> positions = left_drive.get_position_all();
        return (positions[0] + positions[1] + positions[2]) / 3;
    }

    double get_right_drive_raw() {
        std::vector<double> positions = right_drive.get_position_all();
        return (positions[0] + positions[1] + positions[2]) / 3;
    }

    double get_left_drive_sensor() {
        return get_left_drive_raw() / get_drive_tick_per_inch();
    }

    double get_right_drive_sensor() {
        return get_right_drive_raw() / get_drive_tick_per_inch();
    }

    void drive() {
        double forward_stick = curve_left(apply_threshold(master.get_analog(ANALOG_LEFT_Y)));
        double turn_stick = curve_right(apply_threshold(master.get_analog(ANALOG_RIGHT_X)));

        if (fabs(forward_stick) > 0 || fabs(turn_stick) > 0)
            set_drive_power(forward_stick + turn_stick, forward_stick - turn_stick);
        else
            set_drive_power((0 - get_left_drive_sensor()) * ACTIVE_BRAKE_KP, (0 - get_right_drive_sensor()) * ACTIVE_BRAKE_KP);
    }

    double apply_threshold(double input) {
        if (fabs(input) < DEADZONE)
            return 0;
        return input;
    }
}