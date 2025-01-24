#pragma once
#ifndef pp_h
#define pp_h

#define follow_kp 4
#define lookahead_distance 5.0
#define wheelbase 11.6

#include <vector>
#include <utility>

namespace global {
    extern double max_velocity;
    extern std::vector<std::vector<std::pair<double, double>>> paths;
    extern std::vector<std::pair<double, double>> path_data;
    extern void follow_path(int path_index, double max_vel, bool async);
}
#endif