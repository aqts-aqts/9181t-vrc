#include "main.h"

using namespace global;

namespace global {
    double x = 0;
    double y = 0;

    double x_tracking = 0;
    double y_tracking = 0;

    double prev_x = 0;
    double prev_y = 0;

    double prev_x_tracking = 0;
    double prev_y_tracking = 0;

    double current_rotation = 0;
    double current_rotation_rad = 0;
    double prev_rotation_rad = 0;
    double delta_rotation_rad = 0;

    double delta_x_tracking = 0;
    double delta_y_tracking = 0; 

    double delta_x, delta_y = 0;
    double actual_x_change = 0;
    double actual_y_change = 0;   

    void update_sensors() {
        prev_x_tracking = x_tracking;
        prev_y_tracking = y_tracking;
        prev_rotation_rad = current_rotation_rad;

        x_tracking = horizontal_encoder.get_position() / 100.0;
        y_tracking = vertical_encoder.get_position() / 100.0;
        x_tracking /= 360.0 / (wheel_diameter * M_PI);
        y_tracking /= 360.0 / (wheel_diameter * M_PI);
        current_rotation = (imu1.get_rotation() + imu2.get_rotation()) / 2;
        current_rotation_rad = current_rotation * M_PI / 180;
    }

    void position_tracking() {
        delta_x_tracking = x_tracking - prev_x_tracking;
        delta_y_tracking = y_tracking - prev_y_tracking;
        delta_rotation_rad = current_rotation_rad - prev_rotation_rad;

        if (fabs(delta_rotation_rad) > 1e-6) {
            if ((delta_y_tracking > 0 && delta_rotation_rad > 0) || (delta_y_tracking < 0 && delta_rotation_rad < 0)) { // if arc to the right
                delta_x = 2 * sin(delta_rotation_rad / 2) * (delta_x_tracking / delta_rotation_rad + x_offset);
                delta_y = 2 * sin(delta_rotation_rad / 2) * (delta_y_tracking / delta_rotation_rad + y_offset);
            } else { // if arc to the left
                delta_x = 2 * sin(delta_rotation_rad / 2) * (delta_x_tracking / delta_rotation_rad + x_offset);
                delta_y = 2 * sin(delta_rotation_rad / 2) * (delta_y_tracking / delta_rotation_rad + y_offset);
            }
        } else { // didn't turn, don't divide by 0
            delta_x = delta_x_tracking;
            delta_y = delta_y_tracking;
        }

        actual_x_change = cos(prev_rotation_rad) * delta_x + sin(prev_rotation_rad) * delta_y;
        actual_y_change = -sin(prev_rotation_rad) * delta_x + cos(prev_rotation_rad) * delta_y;

        x += actual_x_change;
        y += actual_y_change;
        // coordinate changes with respect to global heading (after rotation matrix applied)
    }

    void odom_thread() {
        while (imu1.is_calibrating() || imu2.is_calibrating())
		    pros::delay(1000);
        
        while (true) {
            update_sensors();
            position_tracking();
            pros::delay(10);
        }
    }
}