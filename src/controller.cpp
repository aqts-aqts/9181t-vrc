#include "main.h"
using namespace global;

namespace global {
    void score_wall_stake(double rpm) {
        wall_stake_motor.move_absolute(WALL_STAKE_POS, rpm);
    }

    void reset_wall_stake(double rpm) {
        wall_stake_motor.move_absolute(0, rpm);
    }
}