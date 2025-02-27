#include "main.h"
#include "pros/rtos.hpp"
using namespace global;

namespace global {
    bool intake_running = false;
    bool colour_sorted = false;
    double intk_volts = 127;


    void distance_test() {
        intake_front.move(127);
        intake_back.move(127);
        int i = 0;
        while (distance.get_distance() >= 90 && i <= 1000000) {
            pros::delay(10);
            i++;
        }
        intake_front.move(0);
        intake_back.move(0);
    }

    void colour_sort_test() {
        colour.set_led_pwm(100);

        pros::Task spin_task([]() {
            colour_sorted = false;
            while (true && !colour_sorted) {
                if (colour.get_rgb().red > 600 && distance.get_distance() < 90) {
                    intake_back.move(0);
                    intake_front.move(0);
                    wall_stake_motor.move_relative(-2600, 200);
                    colour_sorted = true;
                }
                pros::delay(10);
            }
            pros::delay(500);
            //intake_front.move(127);
            //intake_back.move(127);
        });

        intake_front.move(127);
        intake_back.move(127);
    }

    void skills() { // init_angle = 297
        set_drive_constants(0.2, 0.5, 2000, 20, 10, 50);

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
                    if (stuck_time > 500) {
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


        
        turn_to_face_back(12.5, -13, 90);
        wait_pid();

        move_to_back(12.5, -13, 100);
        wait_pid();

        //clamps on:
        clamp.set_value(1);
        pros::delay(500);


        turn_to_face(29, -15, 90);
        wait_pid();

        intake_running = true;
        intk_volts = 127;
        intake_front.move(127);
        intake_back.move(127); 

        pros::delay(500);
        //first ring
        move_to(29, -15, 100);
        wait_pid();

        turn_to_face(77, -39, 90); // -38
        wait_pid();
        //picks up the second ring:
        move_to(77, -39, 100); // -38
        wait_pid();


        //turns to face the center thing
        turn_to_face(62, -42.5, 90);
        wait_pid();

        move_to(62, -42.5, 100);
        wait_pid();


        turn_to_face(60.5, -54, 90);
        wait_pid();
        //heads over to first wallstake  
        intake_front.move(80);
        intake_back.move(80); 
        intake_running = true;
        intk_volts = 80;
        
        move_to(60.5, -54, 40);
        int i = 0;
        while (distance.get_distance() >= 90 && i <= 300) {
            pros::delay(10);
            i++;
        }
        intake_front.move(0);
        intake_back.move(0);
        intake_running = false;
        wait_pid();

        set_drive_constants(0.2, 0.5, 500, 20, 10, 50);

        set_drive_target(-8, 60);
        while (distance.get_distance() >= 60 && i <= 350) {
            intake_front.move(80);
            intake_back.move(80);
            pros::delay(10);
            i++;
        }
        intake_front.move(0);
        intake_back.move(0);
        wait_pid();

        set_drive_target(8, 60);
        while (distance.get_distance() >= 60 && i <= 400) {
            intake_front.move(80);
            intake_back.move(80);
            pros::delay(10);
            i++;
        }
        intake_front.move(0);
        intake_back.move(0);
        wait_pid();

        set_drive_constants(0.2, 0.5, 2000, 20, 10, 50);

        printf("X: %f, Y: %f\n", x, y);

        pros::delay(500);

        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;
        intake_running  = true;

        move_to_back(64, -46, 100);
        wait_pid();

        turn_to_face(8, -46, 90);
        wait_pid();

        move_to(8, -46, 50);
        wait_pid();

        turn_to_face(11, -52, 90);
        wait_pid();

        move_to(11, -52, 100);
        wait_pid();
        //running into wall first time:

        turn_to_face_back(-12, -68, 90);
        wait_pid();

        clamp.set_value(false);

        set_drive_constants(0.2, 0.5, 1000, 20, 10, 50);

        move_to_back(-12, -65, 50);
        wait_pid();

        set_drive_constants(0.2, 0.5, 2000, 20, 10, 50);


        pros::delay(250);

       // set_drive_target(-20, 100);
       // wait_pid();
        
        intake_front.move(0);
        intake_back.move(0); 
        intake_running = false;

        x = 0;
        y = 0;

        move_to(10, 6, 100);
        wait_pid();

        turn_to_face_back(8, 75, 90);
        wait_pid();

        set_drive_constants(0.2, 0.5, 2000, 20, 10, 50);
       
        move_to_back(8, 75, 75);
        wait_pid();

        set_drive_constants(0.2, 0.5, 2000, 20, 10, 50);

        clamp.set_value(1);
        pros::delay(250);


        turn_to_face(32, 85, 90);
        wait_pid();
        intake_front.move(127);
        intake_back.move(127); 
        intk_volts = 127;
        intake_running = true;
        move_to(32, 85, 100);
        wait_pid();
        


        turn_to_face(60, 60, 90);
        wait_pid();

        move_to(60, 60, 100);
        wait_pid();

        intake_front.move(0);
        intake_back.move(0); 
        intake_running = false;

        pros::delay(100);
        
        //turn_to_face_back(32, 85, 80);
        //wait_pid();

       
        move_to_back(32, 85, 80);
        wait_pid();

        intake_front.move(127);
        intake_back.move(127); 
        intk_volts = 127;
        intake_running = true;

        turn_to_face(39, 107, 90);
        wait_pid();

        move_to(39, 107, 100);
        wait_pid();

        turn_to_face(5, 103, 90);
        wait_pid();

        move_to(5, 103, 70);
        wait_pid();


        //last ring second side
        turn_to_face(8, 123, 80);
        wait_pid();

        move_to(8, 123, 70);
        wait_pid();

        //turning to ram into the wall
        turn_to_face_back(-2, 128, 80);
        wait_pid();


        clamp.set_value(0);

        set_drive_constants(0.2, 0.5, 1000, 20, 10, 50);

        move_to_back(-2, 128, 50);
        wait_pid();

        set_drive_constants(0.2, 0.5, 2000, 20, 10, 50);

        x = 0;
        y = 0;

       
        turn_to_face(12, -14, 90);
        wait_pid();
        
        move_to(12, -14, 100);
        wait_pid();

        turn_to_face(44, -14, 80);
        wait_pid();
        
        move_to(44, -14, 100);
        wait_pid();

        intake_front.move(80);
        intake_back.move(80); 
        intk_volts = 80;
        intake_running = false;

        turn_to_face(42, 10000, 80);
        wait_pid();
        
        move_to(42, -2, 40);
        int j = 0;
        while (distance.get_distance() >= 60 && j <= 300) {
            pros::delay(10);
            j++;
        }
        intake_front.move(0);
        intake_back.move(0);
        intake_running = false;
        wait_pid();

        set_drive_target(-8, 60);
        while (distance.get_distance() >= 60 && j <= 350) {
            intake_front.move(80);
            intake_back.move(80);
            pros::delay(10);
            j++;
        }
        intake_front.move(0);
        intake_back.move(0);
        wait_pid();

        set_drive_target(8, 60);
        while (distance.get_distance() >= 60 && j <= 400) {
            intake_front.move(80);
            intake_back.move(80);
            pros::delay(10);
            j++;
        }
        intake_front.move(0);
        intake_back.move(0);
        wait_pid();

        pros::delay(1000);

        wall_stake_motor.move_relative(WALL_STAKE_POS, 200);
        pros::delay(1000);
        wall_stake_motor.move_relative(-WALL_STAKE_POS, 200);
        pros::delay(1000);

        move_to_back(48, -15, 80);
        wait_pid();

        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;
        intake_running = false;


        turn_to_face(83, -37, 80);
        wait_pid();
        
        move_to(83, -37, 70);
        int k = 0;
        while (distance.get_distance() >= 60 && k <= 300) {
            pros::delay(10);
            k++;
        }
        intake_front.move(0);
        intake_back.move(0);
        intake_running  = false;
        wait_pid();

        turn_to_face_back(103, -63, 90);
        wait_pid();

        move_to_back(103, -63, 75);
        wait_pid();

        
        clamp.set_value(1);
        pros::delay(500);
        intake_front.move(127);
        intake_back.move(127);
        intk_volts = 127;
        intake_running  = true;

        turn_to_face(105, -18, 90);
        wait_pid();
        
        move_to(105, -18, 100);
        wait_pid();
        move_to_back(105, -32, 90);
        wait_pid();

        turn_to_face(115, -16, 90);
        wait_pid();
        
        move_to(115, -16, 100);
        wait_pid();

        move_to_back(105, -32, 100);
        wait_pid();

        turn_to_face(82, -13, 90);
        wait_pid();
        
        move_to(82, -13, 90);
        wait_pid();


        intake_front.move(0);
        intake_back.move(0); 
        intake_running  = false;

        turn_to_face(-8, 115, 90);
        wait_pid();

        move_to(-8, 115, 90);
        wait_pid();

        turn_to_face_back(9, 129, 90);
        wait_pid();

        clamp.set_value(0);

        

        






        

        
       




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
    void RedRingSideProvis(){
        colour.set_led_pwm(100);

    

        move_to_back(22, 0, 75);
        wait_pid();

        clamp.set_value(1);

        pros::delay(500);

        intake_back.move(120);
        intake_front.move(120);

        turn_to_face(27, 17, 90);
        wait_pid();
        move_to(27, 17, 100);
        wait_pid();

        turn_to_face(45, 24.5, 90);
        wait_pid();
        move_to(45, 24.5, 95);
        wait_pid();

        set_drive_target(-8, 90);
        wait_pid();

        turn_to_face(47, 19, 90);
        wait_pid();
        move_to(47, 19, 70);
        wait_pid();

        
        turn_to_face(0, -40, 90);
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
        
        move_to(0, -40, 60);
        wait_pid();

        pros::delay(500);
        clamp.set_value(0);

        set_drive_target(-9,90);
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
        wall_stake_motor.move_relative(-600, 200);



        turn_to_face(42, -54, 90);
        wait_pid();
        move_to(42, -54, 60);
        wait_pid();
        

        

    };
}
