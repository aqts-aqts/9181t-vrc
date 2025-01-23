#pragma once
#ifndef pp_h
#define pp_h

#define follow_kp 0.2
#define lookahead_distance 10.0
#define wheelbase 12.0

#include <vector>
#include <utility>

namespace global {
    extern double max_velocity;
    extern std::vector<std::vector<std::pair<double, double>>> paths;
    extern void follow_path();
}
#endif