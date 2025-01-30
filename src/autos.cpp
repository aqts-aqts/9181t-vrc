#include "main.h"
using namespace global;

namespace global {
    void skills() {
        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);


        
        set_turn_target(320, 90);
        wait_pid();

        move_to_back(12.5, -13, 100);
        wait_pid();

        //clamps on:
        clamp.set_value(1);
        pros::delay(500);


        set_turn_target(100, 90);
        wait_pid();

       intake_front.move(100);
       intake_back.move(100); 

        pros::delay(500);
        //first ring
        move_to(30, -13, 85);
        wait_pid();

        set_turn_target(113, 90);
        wait_pid();
        //picks up the second ring:
        move_to(80, -36, 100);
        wait_pid();


        //turns to face the center thing
        set_turn_target(278, 90);
        wait_pid();

        move_to(64, -35, 85);
        wait_pid();


        set_turn_target(172, 90);
        wait_pid();
        //heads over to wallstake
        move_to(57.6, -55, 85);
        wait_pid();


        move_to_back(61, -50, 100);
        wait_pid();

        set_turn_target(270, 90);
        wait_pid();

        move_to(9, -50, 45);
        wait_pid();

        set_turn_target(152, 80);
        wait_pid();

        
        move_to(8, -53, 50);
        wait_pid();

        set_turn_target(60.5, 80);
        wait_pid();

        move_to_back(5, -53, 100);
        wait_pid();

        clamp.set_value(false);
        pros::delay(500);

        move_to(8, -22, 50);
        wait_pid();
        

        set_turn_target(180, 80);
        wait_pid();

        move_to_back(10, -30, 100);
        wait_pid();


        intake_front.move(0);
        intake_back.move(0); 

//Below is garbage
        /*set_turn_target(290, 90);
        wait_pid();

        move_to(66, -42, 100);
        wait_pid();

        intake_front.move(0);
        intake_back.move(0); 
        */
       /* set_turn_target(177, 90);
        wait_pid();

        move_to(46, -42, 85);
        wait_pid();
        
        move_to_back(46, -56, 100);
        wait_pid();

        set_turn_target(270, 90);
        wait_pid();

        move_to(15, -31, 100);
        wait_pid(); */
        
        /*

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
        */
    }
}