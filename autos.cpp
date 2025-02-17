#include "main.h"
using namespace global;

namespace global {
    void skills() {
        
        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);


        
        turn_to_face_back(12.5, -13, 100 );
        wait_pid();

        move_to_back(12.5, -13, 100);
        wait_pid();

        //clamps on:
        clamp.set_value(1);
        pros::delay(500);


        turn_to_face(29, -15, 85 );
        wait_pid();

       intake_front.move(115);
       intake_back.move(115); 

        pros::delay(500);
        //first ring
        move_to(29, -15, 85);
        wait_pid();

        turn_to_face(77, -38, 100);
        wait_pid();
        //picks up the second ring:
        move_to(77, -38, 100);
        wait_pid();


        //turns to face the center thing
        turn_to_face(63, -41, 85);
        wait_pid();

        move_to(63, -41, 85);
        wait_pid();


        turn_to_face(63, -53.5, 80);
        wait_pid();
        //heads over to wallstake
        intake_front.move(85);
        intake_back.move(85); 
        
        move_to(63,-53.5, 90);
        wait_pid();
        //set_drive_target(13.6, 80);
        while (distance.get_distance() >= 60)
            pros::delay(10);
        intake_front.move(0);
        intake_back.move(0);
        wait_pid();

        printf("X: %f, Y: %f\n", x, y);

        pros::delay(1000);


        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        intake_front.move(115);
        intake_back.move(115);

        move_to_back(58, -47, 100);
        wait_pid();


        turn_to_face(10, -47, 45);
        wait_pid();

        move_to(10, -47, 45);
        wait_pid();

        turn_to_face(13, -53, 70);
        wait_pid();

        move_to(13, -53, 50);
        wait_pid();

        turn_to_face_back(-12, -65, 85);
        wait_pid();

        move_to_back(-12, -65, 60);
        wait_pid();


        clamp.set_value(false);
        pros::delay(500);

       // set_drive_target(-20, 100);
       // wait_pid();
        
        intake_front.move(0);
        intake_back.move(0); 
        

        x = 0;
        y = 0;

        move_to(10, 6, 80);
        wait_pid();

        turn_to_face_back(8, 77, 70);
        wait_pid();
       
        move_to_back(8, 77, 70);
        wait_pid();

        clamp.set_value(1);
        pros::delay(500);


        turn_to_face(32, 85, 80);
        wait_pid();
        intake_front.move(106);
        intake_back.move(106); 
      
        move_to(32, 85, 80);
        wait_pid();
        


        turn_to_face(55, 64, 80);
        wait_pid();
        pros::delay(500);

        move_to(55, 64, 100);
        wait_pid();

        intake_front.move(0);
        intake_back.move(0); 

        pros::delay(600);
        
        turn_to_face_back(32, 85, 80);
        wait_pid();

        intake_front.move(106);
        intake_back.move(106); 


        move_to_back(32, 85, 80);
        wait_pid();

        turn_to_face(32, 107, 80);
        wait_pid();

        move_to(32, 107, 80);
        wait_pid();

        turn_to_face(3, 103, 80);
        wait_pid();

        move_to(3, 103, 60);
        wait_pid();

        turn_to_face(11, 121, 80);
        wait_pid();

        move_to(11, 121, 70);
        wait_pid();

        turn_to_face_back(-2, 126, 80);
        wait_pid();
        move_to_back(-2, 126, 80);
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
    void awpBlue() {
        
            move_to_back(-27, 0, 70);
            wait_pid();
            clamp.set_value(1);

            pros::delay(500);

            //turn to 
            turn_to_face(-22, -19, 90);
            wait_pid();

            intake_front.move(115);
            intake_back.move(115); 
            move_to(-22, -19, 50);
            wait_pid();

            turn_to_face(2, 36, 70);
            wait_pid();
            move_to(2, 20, 50);
            wait_pid();

            turn_to_face_back(-10, 30, 70);
            wait_pid();
            intake_front.move(0);
            intake_back.move(0);

            move_to(8, 30, 70);
            wait_pid();
      
            turn_to_face(-24, 26, 70);
            wait_pid();
           


            move_to(-22, 26, 60);
            wait_pid();
            

     
            
    }


}