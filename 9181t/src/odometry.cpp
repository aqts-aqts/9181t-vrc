#include "main.h"
#include "include/global.h"

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
    double current_heading = 0;
    double current_heading_rad = 0;
    double prev_heading_rad = 0;
    double delta_heading_rad = 0;
    double delta_x_tracking = 0;
    double delta_y_tracking = 0; 
    double delta_x, delta_y = 0;
    double actual_x_change = 0;
    double actual_y_change = 0;

    void update_sensors() {
        prev_x_tracking = x_tracking;
        prev_y_tracking = y_tracking;
        prev_heading_rad = current_heading_rad;

        x_tracking = horizontal_encoder.get_position();
        y_tracking = vertical_encoder.get_position();
        current_heading = (imu1.get_rotation() + imu2.get_rotation()) / 2 * 360 / imu_drift;
        current_heading_rad = current_heading * M_PI / 180;
    }

    void position_tracking() {
        delta_x_tracking = x_tracking - prev_x_tracking;
        delta_y_tracking = y_tracking - prev_y_tracking;
        delta_heading_rad = current_heading_rad - prev_heading_rad;

        if (delta_heading_rad != 0) {
            if ((delta_y_tracking > 0 && delta_heading_rad > 0) || (delta_y_tracking < 0 && delta_heading_rad < 0)) { // if arc to the right
                delta_x = 2 * sin(delta_heading_rad / 2) * (delta_x_tracking / delta_heading_rad + x_offset);
                delta_y = 2 * sin(delta_heading_rad / 2) * (delta_y_tracking / delta_heading_rad + y_offset);
            } else { // if arc to the left
                delta_x = 2 * sin(delta_heading_rad / 2) * (delta_x_tracking / delta_heading_rad + x_offset);
                delta_y = 2 * sin(delta_heading_rad / 2) * (delta_y_tracking / delta_heading_rad + y_offset);
            }
        } else { // didn't turn, don't divide by 0
            delta_x = delta_x_tracking;
            delta_y = delta_y_tracking;
        }

        actual_x_change = cos(prev_heading_rad) * delta_x + sin(prev_heading_rad) * delta_y;
        actual_y_change = -sin(prev_heading_rad) * delta_x + cos(prev_heading_rad) * delta_y;
        // coordinate changes with respect to global heading (after rotation matrix applied)
    }

    void odom_thread() {
        x = 0;
        y = 0;
        while (true) {
            update_sensors();
            position_tracking();
            x += actual_x_change;
            y += actual_y_change;
            pros::delay(10);
        }
    }
}