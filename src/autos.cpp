#include "main.h"
using namespace global;

namespace global {
    void skills() {
        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        set_turn_target(52, 90);
        wait_pid();

        set_drive_constants(0.2, 0.5, 500, 20, 10, 50);

        move_to_back(-9.24, -11.82, 100);
        wait_pid();

        set_drive_constants(0.2, 0.5, 4000, 20, 10, 50);

        clamp.set_value(1);
        pros::delay(500);

        set_turn_target(180, 90);
        wait_pid();

        intake_front.move(127);
        intake_back.move(127);

        move_to(-29.24, -11.82, 100);
        wait_pid();

        set_turn_target(197, 90);
        wait_pid();

        move_to(-67.49, -23.515, 100);
        wait_pid();
    }

    void skills1() {
        // score wall stake
        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        set_turn_target(35, 90);
        wait_pid();

        set_drive_constants(0.2, 0.5, 500, 20, 10, 50);

        set_drive_target(-15, 100);
        wait_pid();

        set_drive_constants(0.2, 0.5, 4000, 20, 10, 50);

        clamp.set_value(1);
        pros::delay(500);

        set_turn_target(156, 90); // 142 (+14)
        wait_pid();

        intake_front.move(127);
        intake_back.move(127);

        set_drive_target(20, 100);
        wait_pid();

        set_turn_target(173, 90);
        wait_pid();

        set_drive_target(50, 100);
        wait_pid();

        set_turn_target(346, 90); // 322 (+14)
        wait_pid();

        set_drive_target(27, 100);
        wait_pid();

        set_turn_target(248, 90); // 232 (+14)
        wait_pid();

        set_drive_target(10, 100);
        while (distance.get_distance() > 60)
            pros::delay(10);
        intake_front.move(0);
        intake_back.move(0);
        wait_pid();

        // Score wall stake
        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);

        set_drive_target(-15, 100);
        wait_pid();

        wall_stake_motor.move_absolute(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        set_turn_target(142, 90);
        wait_pid();

        set_drive_target(60, 100);
        wait_pid();

        set_turn_target(-1, 90);
        wait_pid();

        set_drive_target(21, 100);
        wait_pid();

        set_turn_target(-151, 90);
        wait_pid();

        set_drive_target(-20, 100);
        wait_pid();
    }
}