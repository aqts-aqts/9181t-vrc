#include "main.h"
#include "pros/rtos.hpp"
using namespace global;

namespace global {
    bool intake_running = false;
    bool colour_sorted = false;
    double intk_volts = 127;

    void skills() { // init_angle = 297
        colour.set_led_pwm(100);
        pros::Task intake_monitor_task([]() {
            int stuck_time = 0;
            while (true) {
                if (intake_running) {
                    if (fabs((intake_front.get_actual_velocity() + intake_back.get_actual_velocity()) / 2) < 20) {
                        stuck_time += 10;
                    } else {
                        stuck_time = 0;
                    }
                    if (stuck_time > 1000) {
                        intake_front.move(-intk_volts);
                        intake_back.move(-intk_volts);
                        pros::delay(500);
                        intake_front.move(intk_volts);
                        intake_back.move(intk_volts);
                        stuck_time = 0;
                    }
                }
                pros::delay(10);
            }
        });

        
        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        set_turn_timeout(8 + 3);
        
        turn_to_face_back(12.5, -13, 90);
        wait_pid();

        set_drive_timeout(21 + 4);

        move_to_back(12.5, -13, 115);
        wait_pid();

        //clamps on:
        clamp.set_value(1);
        pros::delay(500);

        set_turn_timeout(17 + 3);

        turn_to_face(29, -14, 90);
        wait_pid();

        intake_running = true;
        intk_volts = 127;
        intake_front.move(127);
        intake_back.move(127); 

        pros::delay(500);

        set_drive_timeout(20 + 4);

        //first ring
        move_to(29, -14, 115);
        wait_pid();

        set_turn_timeout(9 + 3);

        turn_to_face(77, -39, 90); // -38
        wait_pid();

        set_drive_timeout(36 + 4);

        //picks up the second ring:
        move_to(77, -39, 115); // -38
        wait_pid();

        set_turn_timeout(20 + 3);

        //turns to face the center thing
        turn_to_face(61, -44.5, 90);
        wait_pid();

        set_drive_timeout(24 + 4);

        move_to(61, -44.5, 115);
        wait_pid();

        set_turn_timeout(13 + 3);

        turn_to_face(60.5, -54, 90);
        wait_pid();
        //heads over to first wallstake  
        intake_front.move(115);
        intake_back.move(115); 
        intake_running = true;
        intk_volts = 80;

        set_drive_timeout(26 + 4);

        pros::Task distance_task([]() {
            int i = 0;
            while (distance.get_distance() >= 90 && i <= 300) {
                pros::delay(10);
                i++;
            }
            intake_front.move(0);
            intake_back.move(0);
            intake_running = false;
        });
        
        move_to(60.5, -54, 115);
        wait_pid();

        set_drive_timeout(16 + 4);

        set_drive_target(-8, 115);
        wait_pid();

        set_drive_timeout(14 + 4);

        set_drive_target(9.25, 115);
        wait_pid();

        printf("X: %f, Y: %f\n", x, y);

        pros::delay(500);

        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS-185, 200);
        pros::delay(500);

        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;
        intake_running  = true;

        set_drive_timeout(20 + 4);

        move_to_back(64, -46, 115);
        wait_pid();

        set_turn_timeout(13 + 3);

        turn_to_face(8, -46, 90);
        wait_pid();

        set_drive_timeout(62 + 4);

        move_to(8, -46, 60); // was 50
        wait_pid();

        set_turn_timeout(17 + 3);

        turn_to_face(11, -52, 90);
        wait_pid();

        set_drive_timeout(20 + 4);

        move_to(11, -52, 115);
        wait_pid();

        pros::delay(200); 
        //running into wall first time:
        
        set_turn_timeout(14 + 3);

        turn_to_face_back(-12, -68, 90);
        wait_pid();

        pros::delay(250);

        clamp.set_value(false);

        intake_front.move(-30);
        intake_back.move(-30);
        intk_volts = -30;
        intake_running  = true;

        set_drive_timeout(20 + 4);

        move_to_back(-12, -65, 50);
        wait_pid();

        pros::delay(250);

       // set_drive_target(-20, 100);
       // wait_pid();
        
        intake_front.move(0);
        intake_back.move(0); 
        intake_running = false;

        x = 0;
        y = 0;

        set_drive_timeout(17 + 4);

        move_to(10, 6, 115);
        wait_pid();

        set_turn_timeout(14 + 3);

        turn_to_face_back(6.5, 75.5, 90);
        wait_pid();

        set_drive_timeout(62 + 4);
       
        move_to_back(6.5, 75.5, 70);
        wait_pid();

        set_turn_timeout(13 + 3);

        clamp.set_value(1);
        pros::delay(250);

        turn_to_face(32, 85, 90);
        wait_pid();
        intake_front.move(127);
        intake_back.move(127); 
        intk_volts = 127;
        intake_running = true;

        set_drive_timeout(21 + 4);

        move_to(32, 85, 115);
        wait_pid();
        
        /*set_turn_timeout(9 + 3);

        turn_to_face(60, 60, 90);
        wait_pid();

        pros::delay(250);

        set_drive_timeout(31 + 4);

        move_to(60, 60, 115);
        wait_pid();

        intake_front.move(0);
        intake_back.move(0); 
        intake_running = false;

        pros::delay(100);
        
        //turn_to_face_back(32, 85, 80);
        //wait_pid();

        set_drive_timeout(40 + 4);
       
        move_to_back(32, 85, 80);
        wait_pid();

        intake_front.move(127);
        intake_back.move(127); 
        intk_volts = 127;
        intake_running = true;*/

        set_turn_timeout(14 + 3);

        turn_to_face(31, 107, 90);
        wait_pid();

        set_drive_timeout(21 + 4);  

        move_to(31, 107, 115);
        wait_pid();

        set_turn_timeout(19 + 3);

        turn_to_face(4, 104, 90);
        wait_pid();

        set_drive_timeout(35 + 4);

        move_to(4, 104, 70);
        wait_pid();


        //last ring second side

        set_turn_timeout(17 + 3);

        turn_to_face(6, 123, 90);
        wait_pid();

        set_drive_timeout(22 + 4);

        move_to(6, 123, 100);
        wait_pid();

        set_turn_timeout(18 + 3);

        //turning to ram into the wall
        turn_to_face_back(-2, 128, 80);
        wait_pid();


        clamp.set_value(0);

        set_drive_timeout(30 + 4);

        move_to_back(-2, 128, 100);
        wait_pid();

        set_turn_timeout(12 + 3);

        x = 0;
        y = 0;

       
        turn_to_face(12, -14, 90);
        wait_pid();

        set_drive_timeout(22 + 4);
        
        move_to(12, -14, 115);
        wait_pid();

        set_turn_timeout(11 + 3);

        turn_to_face(44, -14, 80);
        wait_pid();

        set_drive_timeout(25 + 4);
        
        move_to(44, -14, 115);
        wait_pid();

        intake_front.move(120);
        intake_back.move(120); 
        intk_volts = 120;
        intake_running = true;

        set_turn_timeout(12 + 3);

        turn_to_face(42, 10000, 90);
        wait_pid();

        set_drive_timeout(25 + 4);

        pros::Task distance_task_2([]() {
            int j = 0;
            while (distance.get_distance() >= 60 && j <= 300) {
                pros::delay(10);
                j++;
            }
            intake_front.move(0);
            intake_back.move(0);
            intake_running = false;
        });
        
        move_to(42, -2, 115);
        wait_pid();

        set_drive_timeout(18 + 4);

        set_drive_target(-8, 115);
        wait_pid();

        set_drive_timeout(16 + 4);

        set_drive_target(8, 115);
        wait_pid();

        set_drive_timeout(22 + 4);

        pros::delay(500);

        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS -125, 200);
        pros::delay(500);

        move_to_back(48, -15, 80);
        wait_pid();

        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;
        intake_running = false;

        set_turn_timeout(18 + 3);

        turn_to_face(83, -37, 80);
        wait_pid();

        set_drive_timeout(31 + 4);

        pros::Task distance_task_3([]() {
            int k = 0;
            while (distance.get_distance() >= 60 && k <= 300) {
            pros::delay(10);
            k++;
            }
            intake_front.move(0);
            intake_back.move(0);
            intake_running = false;
        });
        
        move_to(83, -37, 115);
        wait_pid();

        set_turn_timeout(17 + 3);

        turn_to_face_back(104, -63, 90);
        wait_pid();

        set_drive_timeout(33 + 4);

        move_to_back(104, -63, 115);
        wait_pid();

        
        clamp.set_value(1);
        pros::delay(500);
        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;

        set_drive_timeout(20 + 4);

        set_drive_target(13, 100);
        wait_pid();

        set_turn_timeout(9 + 3);

        turn_to_face(104, -7, 90);
        wait_pid();

        intake_running  = false;

        set_drive_timeout(39 + 4);

        move_to(104, -7, 75);
        wait_pid();

        set_drive_timeout(26 + 4);

        move_to_back(105, -32, 115);
        wait_pid();

        intake_running = true;

        set_turn_timeout(9 + 3);

        turn_to_face(115.5, -16, 90);
        wait_pid();

        set_drive_timeout(25 + 4);
        
        move_to(115.5, -16, 115);
        wait_pid();

        set_drive_timeout(23 + 4);

        turn_to_face_back(115, -4, 90);
        wait_pid();

        intake_front.move(-60);
        intake_back.move(-60);
        intk_volts = -60;

        clamp.set_value(0);

        set_drive_timeout(49 + 4);

        turn_to_face(107.5, -40, 90);
        wait_pid();

        move_to(107.5, -40, 115);
        wait_pid();

        turn_to_face(121, -110,127);
        wait_pid();

        move_to(121, -110, 127);
        wait_pid();

        



      





        

        






        

        
       




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

    void skills_old() { // init_angle = 297
        colour.set_led_pwm(100);
        pros::Task intake_monitor_task([]() {
            int stuck_time = 0;
            while (true) {
                if (intake_running) {
                    if (fabs((intake_front.get_actual_velocity() + intake_back.get_actual_velocity()) / 2) < 20) {
                        stuck_time += 10;
                    } else {
                        stuck_time = 0;
                    }
                    if (stuck_time > 1000) {
                        intake_front.move(-intk_volts);
                        intake_back.move(-intk_volts);
                        pros::delay(500);
                        intake_front.move(intk_volts);
                        intake_back.move(intk_volts);
                        stuck_time = 0;
                    }
                }
                pros::delay(10);
            }
        });

        
        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        set_turn_timeout(8 + 3);
        
        turn_to_face_back(12.5, -13, 90);
        wait_pid();

        set_drive_timeout(21 + 4);

        move_to_back(12.5, -13, 115);
        wait_pid();

        //clamps on:
        clamp.set_value(1);
        pros::delay(500);

        set_turn_timeout(17 + 3);

        turn_to_face(29, -14, 90);
        wait_pid();

        intake_running = true;
        intk_volts = 127;
        intake_front.move(127);
        intake_back.move(127); 

        pros::delay(500);

        set_drive_timeout(20 + 4);

        //first ring
        move_to(29, -14, 115);
        wait_pid();

        set_turn_timeout(9 + 3);

        turn_to_face(77, -39, 90); // -38
        wait_pid();

        set_drive_timeout(36 + 4);

        //picks up the second ring:
        move_to(77, -39, 115); // -38
        wait_pid();

        set_turn_timeout(20 + 3);

        //turns to face the center thing
        turn_to_face(61, -44.5, 90);
        wait_pid();

        set_drive_timeout(24 + 4);

        move_to(61, -44.5, 115);
        wait_pid();

        set_turn_timeout(13 + 3);

        turn_to_face(59.25, -54, 90);
        wait_pid();
        //heads over to first wallstake  
        intake_front.move(115);
        intake_back.move(115); 
        intake_running = true;
        intk_volts = 80;

        set_drive_timeout(26 + 4);

        pros::Task distance_task([]() {
            int i = 0;
            while (distance.get_distance() >= 90 && i <= 300) {
                pros::delay(10);
                i++;
            }
            intake_front.move(0);
            intake_back.move(0);
            intake_running = false;
        });
        
        move_to(59.25, -54, 115);
        wait_pid();

        set_drive_timeout(16 + 4);

        set_drive_target(-8, 115);
        wait_pid();

        set_drive_timeout(14 + 4);

        set_drive_target(9.25, 115);
        wait_pid();

        printf("X: %f, Y: %f\n", x, y);

        pros::delay(500);

        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS-185, 200);
        pros::delay(500);

        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;
        intake_running  = true;

        set_drive_timeout(20 + 4);

        move_to_back(64, -46, 115);
        wait_pid();

        set_turn_timeout(13 + 3);

        turn_to_face(8, -46, 90);
        wait_pid();

        set_drive_timeout(62 + 4);

        move_to(8, -46, 60); // was 50
        wait_pid();

        set_turn_timeout(17 + 3);

        turn_to_face(11, -52, 90);
        wait_pid();

        set_drive_timeout(20 + 4);

        move_to(11, -52, 115);
        wait_pid();

        pros::delay(200); 
        //running into wall first time:
        
        set_turn_timeout(14 + 3);

        turn_to_face_back(-12, -68, 90);
        wait_pid();

        pros::delay(250);

        clamp.set_value(false);

        intake_front.move(-30);
        intake_back.move(-30);
        intk_volts = -30;
        intake_running  = true;

        set_drive_timeout(20 + 4);

        move_to_back(-12, -65, 50);
        wait_pid();

        pros::delay(250);

       // set_drive_target(-20, 100);
       // wait_pid();
        
        intake_front.move(0);
        intake_back.move(0); 
        intake_running = false;

        x = 0;
        y = 0;

        set_drive_timeout(17 + 4);

        move_to(10, 6, 115);
        wait_pid();

        set_turn_timeout(14 + 3);

        turn_to_face_back(6.5, 75.5, 90);
        wait_pid();

        set_drive_timeout(62 + 4);
       
        move_to_back(6.5, 75.5, 70);
        wait_pid();

        set_turn_timeout(13 + 3);

        clamp.set_value(1);
        pros::delay(250);

        turn_to_face(32, 85, 90);
        wait_pid();
        intake_front.move(127);
        intake_back.move(127); 
        intk_volts = 127;
        intake_running = true;

        set_drive_timeout(21 + 4);

        move_to(32, 85, 115);
        wait_pid();
        
        /*set_turn_timeout(9 + 3);

        turn_to_face(60, 60, 90);
        wait_pid();

        pros::delay(250);

        set_drive_timeout(31 + 4);

        move_to(60, 60, 115);
        wait_pid();

        intake_front.move(0);
        intake_back.move(0); 
        intake_running = false;

        pros::delay(100);
        
        //turn_to_face_back(32, 85, 80);
        //wait_pid();

        set_drive_timeout(40 + 4);
       
        move_to_back(32, 85, 80);
        wait_pid();

        intake_front.move(127);
        intake_back.move(127); 
        intk_volts = 127;
        intake_running = true;*/

        set_turn_timeout(14 + 3);

        turn_to_face(31, 107, 90);
        wait_pid();

        set_drive_timeout(21 + 4);  

        move_to(31, 107, 115);
        wait_pid();

        set_turn_timeout(19 + 3);

        turn_to_face(4, 104, 90);
        wait_pid();

        set_drive_timeout(35 + 4);

        move_to(4, 104, 70);
        wait_pid();


        //last ring second side

        set_turn_timeout(17 + 3);

        turn_to_face(6, 123, 90);
        wait_pid();

        set_drive_timeout(22 + 4);

        move_to(6, 123, 100);
        wait_pid();

        set_turn_timeout(18 + 3);

        //turning to ram into the wall
        turn_to_face_back(-2, 128, 80);
        wait_pid();


        clamp.set_value(0);

        set_drive_timeout(30 + 4);

        move_to_back(-2, 128, 100);
        wait_pid();

        set_turn_timeout(12 + 3);

        x = 0;
        y = 0;

       
        turn_to_face(12, -14, 90);
        wait_pid();

        set_drive_timeout(22 + 4);
        
        move_to(12, -14, 115);
        wait_pid();

        set_turn_timeout(11 + 3);

        turn_to_face(44, -14, 80);
        wait_pid();

        set_drive_timeout(25 + 4);
        
        move_to(44, -14, 115);
        wait_pid();

        intake_front.move(120);
        intake_back.move(120); 
        intk_volts = 120;
        intake_running = true;

        set_turn_timeout(12 + 3);

        turn_to_face(42, 10000, 90);
        wait_pid();

        set_drive_timeout(25 + 4);

        pros::Task distance_task_2([]() {
            int j = 0;
            while (distance.get_distance() >= 60 && j <= 300) {
                pros::delay(10);
                j++;
            }
            intake_front.move(0);
            intake_back.move(0);
            intake_running = false;
        });
        
        move_to(42, -2, 115);
        wait_pid();

        set_drive_timeout(18 + 4);

        set_drive_target(-8, 115);
        wait_pid();

        set_drive_timeout(16 + 4);

        set_drive_target(8, 115);
        wait_pid();

        set_drive_timeout(22 + 4);

        pros::delay(500);

        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS -125, 200);
        pros::delay(500);

        move_to_back(48, -15, 80);
        wait_pid();

        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;
        intake_running = false;

        set_turn_timeout(18 + 3);

        turn_to_face(83, -37, 80);
        wait_pid();

        set_drive_timeout(31 + 4);

        pros::Task distance_task_3([]() {
            int k = 0;
            while (distance.get_distance() >= 60 && k <= 300) {
            pros::delay(10);
            k++;
            }
            intake_front.move(0);
            intake_back.move(0);
            intake_running = false;
        });
        
        move_to(83, -37, 115);
        wait_pid();

        set_turn_timeout(17 + 3);

        turn_to_face_back(104, -63, 90);
        wait_pid();

        set_drive_timeout(33 + 4);

        move_to_back(104, -63, 115);
        wait_pid();

        
        clamp.set_value(1);
        pros::delay(500);
        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;

        set_drive_timeout(20 + 4);

        set_drive_target(10, 100);
        wait_pid();

        set_turn_timeout(9 + 3);

        turn_to_face(105, -7, 90);
        wait_pid();

        intake_running  = false;

        set_drive_timeout(39 + 4);

        move_to(105, -7, 75);
        wait_pid();

        set_drive_timeout(26 + 4);

        move_to_back(105, -32, 115);
        wait_pid();

        intake_running = true;

        set_turn_timeout(9 + 3);

        turn_to_face(115.5, -16, 90);
        wait_pid();

        set_drive_timeout(25 + 4);
        
        move_to(115.5, -16, 115);
        wait_pid();

        set_drive_timeout(23 + 4);

        move_to_back(105, -32, 115);
        wait_pid();

        set_turn_timeout(12 + 3);

        turn_to_face(82, -13, 90);
        wait_pid();

        set_drive_timeout(25 + 4);
        
        move_to(82, -13, 115);
        wait_pid();

        set_turn_timeout(8 + 3);

        turn_to_face_back(81, -36, 90);
        wait_pid();

        set_drive_timeout(27 + 4);

        move_to_back(81,  -36, 115);
        wait_pid();

        clamp.set_value(0);

        intake_front.move(-80);
        intake_back.move(-80);
        intk_volts = -80;
        intake_running  = true;

        set_turn_timeout(17 + 3);

        turn_to_face(111, -53, 90);
        wait_pid();

        set_drive_timeout(30 + 4);

        move_to(111, -53, 115);
        wait_pid();

        set_turn_timeout(13 + 3);

        turn_to_face(115, -4, 90);
        wait_pid();

        set_drive_timeout(49 + 4);

        move_to(115, -4, 90);
        wait_pid();

        set_drive_target(-35, 127);
        wait_pid();

        turn_to_face_back(124, -121, 127);
        wait_pid();

        move_to_back(124, -121, 127);
        wait_pid();

        set_drive_target(10, 127);
        wait_pid();





        

        






        

        
       




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

    void awpBlue() { // init angle = 90
         

        colour.set_led_pwm(100);
        
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

        pros::Task spin_task([]() {
            colour_sorted = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().red > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(127);
            intake_back.move(127);
        });

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

    void awpRed() { // init angle = 90
         

        colour.set_led_pwm(100);
        
        move_to_back(-27, 0, 70);
        wait_pid();
        clamp.set_value(1);

        pros::delay(500);

        //turn to 
        turn_to_face(-22, 19, 90);
        wait_pid();

        intake_front.move(115);
        intake_back.move(115); 
        move_to(-22, 19, 50);
        wait_pid();

        pros::Task spin_task([]() {
            colour_sorted = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().blue > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });

        turn_to_face(2, -36, 70);
        wait_pid();
        move_to(2, -20, 50);
        wait_pid();

        turn_to_face_back(-10, -30, 70);
        wait_pid();
        intake_front.move(0);
        intake_back.move(0);

        move_to(8, -30, 70);
        wait_pid();
    
        turn_to_face(-24, -26, 70);
        wait_pid();
        
        move_to(-22, -26, 60);
        wait_pid();
    }

    void awpSoloBlue() { // init angle = 90
        
        colour.set_led_pwm(100);

        holding = true;

        pros::Task wall_stake_monitor_task([]() {
            while (true) {
                if (holding && fabs(wall_stake_motor.get_position()) > 25) {
                    wall_stake_motor.move(-wall_stake_motor.get_position() * 0.2); // kp = 0.2
                }
                pros::delay(10);
            }
        });
        
        move_to_back(-19, 0, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(120);
        intake_front.move(120);

        turn_to_face(-29.5, 17, 90);
        wait_pid();
        move_to(-29.5, 17, 90);
        wait_pid();

        turn_to_face(-21, 25, 90);
        wait_pid();
        move_to(-21, 25, 90);
        wait_pid();

        pros::Task spin_task([]() {
            colour_sorted = false;
            holding = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().red > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });


        turn_to_face(10, -36, 90);
        wait_pid();
        move_to(10, -36, 50);
        wait_pid();

        /*clamp.set_value(0);

        turn_to_face_back(-22.82, -49.88, 60);
        wait_pid();
        move_to_back(-22.82, -49.88, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        turn_to_face(-24.3, -73, 90);
        wait_pid();
        move_to(-24.3, -73, 90);
        wait_pid();

        turn_to_face(-43.06, -46.75, 90);
        wait_pid();
        move_to(-43.06, -46.75, 90);
        wait_pid();
        */
    }
    void awpSoloRedNew() { // init angle = 90
        
        colour.set_led_pwm(100);

        holding = true;

        pros::Task wall_stake_monitor_task([]() {
            while (true) {
                if (holding && fabs(wall_stake_motor.get_position()) > 25) {
                    wall_stake_motor.move(-wall_stake_motor.get_position() * 0.2); // kp = 0.2
                }
                pros::delay(10);
            }
        });
        
        move_to_back(-19, 0, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(120);
        intake_front.move(120);

        turn_to_face(-28.5, -17, 90);
        wait_pid();
        move_to(-28.5, -17, 90);
        wait_pid();

        turn_to_face(-21, -25, 90);
        wait_pid();
        move_to(-21, -25, 90);
        wait_pid();

        pros::Task spin_task([]() {
            colour_sorted = false;
            holding = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().red > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });


        turn_to_face(10, 36, 90);
        wait_pid();
        move_to(10, 36, 50);
        wait_pid();

        /*clamp.set_value(0);

        turn_to_face_back(-22.82, -49.88, 60);
        wait_pid();
        move_to_back(-22.82, -49.88, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        turn_to_face(-24.3, -73, 90);
        wait_pid();
        move_to(-24.3, -73, 90);
        wait_pid();

        turn_to_face(-43.06, -46.75, 90);
        wait_pid();
        move_to(-43.06, -46.75, 90);
        wait_pid();
        */
    }

    void awpSoloRed() { // init angle = 90
        colour.set_led_pwm(100);

        holding = true;

        pros::Task wall_stake_monitor_task([]() {
            while (true) {
                if (holding && fabs(wall_stake_motor.get_position()) > 25) {
                    wall_stake_motor.move(-wall_stake_motor.get_position() * 0.2); // kp = 0.2
                }
                pros::delay(10);
            }
        });
        
        move_to_back(-19, 0, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(120);
        intake_front.move(120);

        turn_to_face(-27, -17, 90);
        wait_pid();
        move_to(-27, -17, 90);
        wait_pid();

        turn_to_face(-21, -25, 90);
        wait_pid();
        move_to(-21, -25, 90);
        wait_pid();

        pros::Task spin_task([]() {
            colour_sorted = false;
            holding = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().blue > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });


        turn_to_face(10, 36, 90);
        wait_pid();
        move_to(10, 36, 50);
        wait_pid();     

        
        clamp.set_value(0);

        turn_to_face_back(-22.82, 49.88, 60);
        wait_pid();
        move_to_back(-22.82, 49.88, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        turn_to_face(-24.3, 73, 90);
        wait_pid();
        move_to(-24.3, 73, 90);
        wait_pid();

        turn_to_face(-43.06, 46.75, 90);
        wait_pid();
        move_to(-43.06, 46.75, 90);
        wait_pid();
    }

    void halfAwpRed() { // init angle = 90

        colour.set_led_pwm(100);
        
        move_to_back(-19, 0, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(120);
        intake_front.move(120);

        turn_to_face(-37, -17, 90);
        wait_pid();
        move_to(-37, -17, 90);
        wait_pid();

        /*turn_to_face(-21, -25, 90);
        wait_pid();
        move_to(-21, -25, 90);
        wait_pid();

        pros::Task spin_task([]() {
            colour_sorted = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().blue > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });


        turn_to_face(10, 36, 90);
        wait_pid();
        move_to(10, 36, 50);
        wait_pid();

        clamp.set_value(0);
        */
    }

    void halfAwpBlue() { // init angle = 90

        colour.set_led_pwm(100);
        
        move_to_back(-19, 0, 65);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(120);
        intake_front.move(120);

        turn_to_face(-37, 17, 90);
        wait_pid();
        move_to(-37, 17, 90);
        wait_pid();

        turn_to_face(-21, 25, 90);
        wait_pid();
        move_to(-21, 25, 90);
        wait_pid();

        pros::Task spin_task([]() {
            colour_sorted = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().red > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });


        turn_to_face(10, -36, 90);
        wait_pid();
        move_to(10, -36, 50);
        wait_pid();

        clamp.set_value(0);
    }
    void RedRingSideProvis(){ // init angle = 270
        colour.set_led_pwm(100);

        x = -7;

        move_to_back(22.25, 0, 75);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(127);
        intake_front.move(127);

        turn_to_face(27, 17, 90);
        wait_pid();
        move_to(27, 17, 100);
        wait_pid();

        turn_to_face(44.25, 24.5, 90);
        wait_pid();
        move_to(44.25, 24.5, 95);
        wait_pid();

        pros::delay(500);

        set_drive_target(-8, 90);
        wait_pid();

        turn_to_face(44.5, 19, 90);
        wait_pid();
        move_to(44.5, 19, 70);
        wait_pid();

        pros::delay(500);

        turn_to_face(10, -42.5, 90);
        wait_pid();

        pros::delay(250);
        
        pros::Task spin_task([]() {
            colour_sorted = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().blue > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });
        
        move_to(10, -42.5, 60);
        wait_pid();

        pros::delay(500);
        

        /*set_drive_target(-9,90);
        wait_pid();
        set_drive_target(9,90);
        wait_pid();

        

        turn_to_face_back(24, -49, 90);
        wait_pid();
        move_to_back(24, -49, 60);
        wait_pid();

        clamp.set_value(1);
        pros::delay(500);

        turn_to_face(27, -78, 90);
        wait_pid();
        move_to(27, -78, 90);
        wait_pid();
        wall_stake_motor.move_relative(-600, 200);*/



        turn_to_face(38, -49, 90);
        wait_pid();
        move_to(38, -49, 60);
        wait_pid();
        

        

    };

    void BlueRingSideProvis(){ // init angle = 270
        colour.set_led_pwm(100);

    

        move_to_back(22, 0, 75);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(120);
        intake_front.move(120);

        turn_to_face(27, -17, 90);
        wait_pid();
        move_to(27, -17, 100);
        wait_pid();

        turn_to_face(45, -24.5, 90);
        wait_pid();
        move_to(45, -24.5, 95);
        wait_pid();

        set_drive_target(-8, 90);
        wait_pid();

        turn_to_face(47, -19, 90);
        wait_pid();
        move_to(47, -19, 70);
        wait_pid();

        
        turn_to_face(0, 40, 90);
        wait_pid();
        
        pros::Task spin_task([]() {
            colour_sorted = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().red > 1000 && distance.get_distance() < 60) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2000, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            intake_front.move(120);
            intake_back.move(120);
        });
        
        /*move_to(0, 40, 60);
        wait_pid();

        pros::delay(500);
        clamp.set_value(0);

        set_drive_target(-9,90);
        wait_pid();
        set_drive_target(9,90);
        wait_pid();

        

        turn_to_face_back(24, 49, 90);
        wait_pid();
        move_to_back(24, 49, 60);
        wait_pid();

        clamp.set_value(1);
        pros::delay(500);

        turn_to_face(27, 78, 90);
        wait_pid();
        move_to(27, 78, 90);
        wait_pid();
        wall_stake_motor.move_relative(-600, 200);



        turn_to_face(42, 54, 90);
        wait_pid();
        move_to(42, 54, 60);
        wait_pid();*/
        

        

    };
}




void Blueringneg(){ // init angle = 270
    colour.set_led_pwm(100);

    x = -7;

    move_to_back(22.25, 0, 75);
    wait_pid();

    clamp.set_value(1);

    pros::delay(500);

    intake_back.move(127);
    intake_front.move(127);

    turn_to_face(27, -17, 90);
    wait_pid();
    move_to(27, -17, 100);
    wait_pid();

    turn_to_face(44.25, -24.5, 90);
    wait_pid();
    move_to(44.25, -24.5, 95);
    wait_pid();

    pros::delay(500);

    set_drive_target(-8, 90);
    wait_pid();

    turn_to_face(44.5, -19, 90);
    wait_pid();
    move_to(44.5, -19, 70);
    wait_pid();

    pros::delay(500);

    turn_to_face(10, 42.5, 90);
    wait_pid();

    pros::delay(250);
    
    pros::Task spin_task([]() {
        colour_sorted = false;
        while (true && !colour_sorted) {
            if (colour.get_rgb().blue > 1000 && distance.get_distance() < 60) {
                intake_back.move(0);
                intake_front.move(0);
                wall_stake_motor.move_relative(-2000, 200);
                colour_sorted = true;
            }
            pros::delay(10);
        }
        pros::delay(500);
        intake_front.move(120);
        intake_back.move(120);
    });
    
    move_to(10, 42.5, 60);
    wait_pid();

    pros::delay(500);
    

    /*set_drive_target(-9,90);
    wait_pid();
    set_drive_target(9,90);
    wait_pid();

    

    turn_to_face_back(24, -49, 90);
    wait_pid();
    move_to_back(24, -49, 60);
    wait_pid();

    clamp.set_value(1);
    pros::delay(500);

    turn_to_face(27, -78, 90);
    wait_pid();
    move_to(27, -78, 90);
    wait_pid();
    wall_stake_motor.move_relative(-600, 200);*/



    turn_to_face(38, 49, 90);
    wait_pid();
    move_to(38, 49, 60);
    wait_pid();
    

    

};


void stakeside(){














};
