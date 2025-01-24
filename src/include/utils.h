#pragma once
#ifndef utils_h
#define utils_h

#include <string>

namespace global {
    extern void read_waypoints_from_sd(const std::string& file_name);
    extern void read_waypoints_from_src(const std::string& file_name);
}
#endif