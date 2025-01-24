#include "main.h"
using namespace global;

namespace global {
    void read_waypoints_from_sd(const std::string& file_name) {
        std::vector<std::pair<double, double>> waypoints;

        FILE* file = fopen(("/usd/" + file_name).c_str(), "r");
        if (file == nullptr) {
            printf("Failed to open file: %s", file_name.c_str());
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            double x_pose, y_pose;
            if (sscanf(line, "%lf,%lf", &x_pose, &y_pose) == 2) {
                waypoints.emplace_back(x_pose, y_pose);
            }
        }

        paths.push_back(waypoints);
        int slot = paths.size() - 1;

        fclose(file);
        pros::lcd::print(10, "Loaded %d waypoints into slot %d", waypoints.size(), slot);
    }

    void read_waypoints_from_src(const std::string& file_name) {
        std::vector<std::pair<double, double>> waypoints;

        // Open the file in the `src` folder
        FILE* file = fopen(("src/" + file_name).c_str(), "r");
        if (file == nullptr) {
            printf("Failed to open file: %s", file_name.c_str());
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            double x_pose, y_pose;
            // Parse the line for two comma-separated double values
            if (sscanf(line, "%lf,%lf", &x_pose, &y_pose) == 2) {
                waypoints.emplace_back(x_pose, y_pose);
            }
        }

        // Store the waypoints into the global paths vector
        paths.push_back(waypoints);
        int slot = paths.size() - 1;

        fclose(file);
        pros::lcd::print(10, "Loaded %d waypoints into slot %d", waypoints.size(), slot);
    }
}