#pragma once
#ifndef controller_h
#define controller_h

#define WALL_STAKE_POS 1680

namespace global {
    extern void score_wall_stake(double rpm = 200);
    extern void reset_wall_stake(double rpm = 200);
}
#endif