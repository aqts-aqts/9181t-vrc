#include "main.h"
using namespace global;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	intake_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intake_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	wall_stake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	imu1.reset();
	imu1.tare();
	imu2.reset();
	imu2.tare();

	horizontal_encoder.reset_position();
	vertical_encoder.reset_position();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

void auto1() {
	// dont change these unless you know what youre doing (i ask you or chatgpt)
	// these control how the robot drives, paste into chatgpt if something is off about it
	// right click the "set_drive_constants" or "set_turn_constants" part, click "go to definition"
	// and then copy the function there (starting from "void" to the last "}") into chatgpt as well
	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);
	
	// functions to use for autos
	// note: you have to use wait_pid() after:
	// set_drive_target or set_turn_target or move_to or turn_to_face or turn_to_face_back
	// or else the robot wont wait for the movement to be done before continuing
	// power is from 0-127, ~100 is ideal so the robot can correct itself
	// distance in inches, angle in degrees, x and y in inches
	// get rid of the // in front of the function you want to use

	move_to_back(0, 12, 100);
	wait_pid();
	set_turn_target(-90, 80);
	wait_pid();
	set_drive_target(-6, 80);
	wait_pid();
	
	
	intake_front.move(100);
	intake_back.move(100);
	
	pros::delay(700);

	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	set_drive_target(6, 100);
	wait_pid();
	set_turn_target(-232, 80);
	wait_pid();
	set_drive_target(-34, 60);
	wait_pid();
	
	pros::delay(300);
	clamp.set_value(true);
	pros::delay(650);

	wait_pid();
	set_turn_target(-10, 80);
	wait_pid();
	intake_front.move(100);
	intake_back.move(100);
	set_drive_target(28, 100);
	pros::delay(2000);


	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	set_turn_target(15, 80);
	wait_pid();

	
	set_drive_target(-36, 100);
	wait_pid();



	// set_drive_target(distance, power) - drive a certain distance at a certain power
	// set_turn_target(angle, power) - turn a certain angle at a certain power
	// move_to(x, y, power) - move to a certain x and y position at a certain power (WONT TURN BEFORE)
	// turn_to_face(x, y, power) - turn to face a certain x and y position at a certain power
	// turn_to_face_back(x, y, power) - turn to face with the back a certain x and y position at a certain power
	// set_drive_power(left_power, right_power) - set the left and right drive power to a certain value (no pid/odom)
	// wait_pid() - wait until the robot has reached the target
	// wait_drive(distance) - wait until the robot has traveled distance (WONT WAIT FOR THE REST OF THE MOVEMENT)
	// wait_turn(angle) - wait until the robot has turned angle (WONT WAIT FOR THE REST OF THE MOVEMENT)

	// this point important
	// when using move_to ALWAYS use turn_to_face first if the direction isnt already faced
	// move_to DOESNT TURN THE ROBOT IT JUST MOVES THE DISTANCE BETWEEN THE ROBOT AND THE POINT
	// WITHOUT LOOKING WHICH WAY ITS GOING

	// if you want to make another auto just move the code of the auto you just made
	// to auto2, auto3, or auto4 inside the function (in between the { and })
	// so like:
	// void auto2() {
	//     set_drive_target(10, 100);
	//     wait_pid();
	// }
	// but keep set_drive_constants and set_turn_constants at the top of the function
	// ill deal with getting which auto to run tomorrow
}

void auto2() {

	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);

	set_drive_target(-11.5, 100);
	wait_pid();
	set_turn_target(90, 100);
	wait_pid();
	set_drive_target(-7, 110);
	wait_pid();

	intake_front.move(110);
	intake_back.move(110);
	
	pros::delay(800);
	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	set_drive_target(7, 110);

	wait_pid();
	set_turn_target(232, 80);
	wait_pid();
	set_drive_target(-36, 110);
	wait_pid();
	pros::delay(300);
	clamp.set_value(true);
	pros::delay(650);
	wait_pid();
	set_turn_target(0, 100);
	wait_pid();
	intake_front.move(100);
	intake_back.move(100);
	set_drive_target(28, 110);
	pros::delay(2000);
	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	intake_front.move(100);
	intake_back.move(100);
	set_turn_target(74, 100);
	wait_pid();
	set_drive_target(8, 110);
	wait_pid();

	


}

void auto3() {

	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);
	
	// functions to use for autos
	// note: you have to use wait_pid() after:
	// set_drive_target or set_turn_target or move_to or turn_to_face or turn_to_face_back
	// or else the robot wont wait for the movement to be done before continuing
	// power is from 0-127, ~100 is ideal so the robot can correct itself
	// distance in inches, angle in degrees, x and y in inches
	// get rid of the // in front of the function you want to use

	move_to_back(0, 12, 100);
	wait_pid();
	set_turn_target(90, 80);
	wait_pid();
	set_drive_target(-5.7, 80);
	wait_pid();
	
	
	intake_front.move(100);
	intake_back.move(100);
	
	pros::delay(700);

	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	set_drive_target(5.7, 100);
	wait_pid();
	set_turn_target(232, 80);
	wait_pid();
	set_drive_target(-34, 60);
	wait_pid();
	
	pros::delay(300);
	clamp.set_value(true);
	pros::delay(650);

	wait_pid();
	set_turn_target(10, 80);
	wait_pid();
	intake_front.move(100);
	intake_back.move(100);
	set_drive_target(28, 100);
	pros::delay(2500);


	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	set_turn_target(-15, 80);
	wait_pid();

	
	set_drive_target(-33, 100);
	wait_pid();

}

void auto4() {
	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);

	set_drive_target(-11.5, 100);
	wait_pid();
	set_turn_target(-90, 100);
	wait_pid();
	set_drive_target(-5.7, 90);
	wait_pid();

	intake_front.move(110);
	intake_back.move(110);
	
	pros::delay(800);
	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	set_drive_target(5.7, 90);

	wait_pid();
	set_turn_target(-232, 80);
	wait_pid();
	set_drive_target(-36, 80);
	wait_pid();

	pros::delay(300);
	clamp.set_value(true);
	pros::delay(650);
	wait_pid();

	set_turn_target(0, 100);
	wait_pid();
	intake_front.move(100);
	intake_back.move(100);
	set_drive_target(28, 110);
	pros::delay(2000);
	intake_front.move(0);
	intake_back.move(0);
	wait_pid();
	intake_front.move(100);
	intake_back.move(100);
	set_turn_target(-85, 100);
	wait_pid();
	set_drive_target(12, 110);
	wait_pid();
}



void skills_auto(){
	
	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);
	intake_front.move(127);
	intake_back.move(127);
	
	pros::delay(500);
	intake_front.move(0);
	intake_back.move(0);

	set_drive_target(11, 100);
	wait_pid();
	set_turn_target(-90, 100);
	wait_pid();
	set_drive_target(-19, 75);
	wait_pid();
	clamp.set_value(true);
	pros::delay(500);

	set_turn_target(5, 100);
	wait_pid();

	intake_front.move(95);
	intake_back.move(95);
	set_drive_target(26, 120);

	wait_pid();
	pros::delay(500);

	set_turn_target(-55, 100);
	wait_pid();

	set_drive_target(30, 110);
	wait_pid();

	set_turn_target(45, 100);
	wait_pid();

	set_drive_target(37, 110);
	wait_pid();
	
	//// THIS IS WALL STSKE so play around with limit switch
	//spin till limits
	/*
	intake_front.move(0);
	intake_back.move(0);

	wall_stake_motor.move(100);
	pros::delay(500);
	//this should move for 270 motor degrees idk how to use pros for this and im in a rush so I just have it in time. 
	wall_stake_motor.move(0); */

	set_turn_target(90, 100);
	wait_pid();


	set_drive_target(28,80);
	wait_pid();
	
	set_turn_target(180, 100);
	wait_pid();
	set_drive_target(24, 110);
	wait_pid();
	set_turn_target(90, 100);
	wait_pid();
	set_drive_target(6, 110);
	wait_pid();	

	//set_drive_target(-4, 110);
	//wait_pid();
	
	
	//THiS IS TO SCORE WALLSTAKE

	set_turn_target(0, 100);
	wait_pid();
	//intake_front.move(127);
	//intake_back.move(127);

	set_drive_target(45, 110);
	wait_pid();
	set_turn_target(-45, 100);
	wait_pid();
	set_drive_target(14, 110);
	wait_pid();

	set_turn_target(-120, 100);
	wait_pid();
	set_drive_target(4, 110);
	wait_pid();
	set_drive_target(-3, 110);
	wait_pid();
	//clamp.set_value(false);

	set_drive_target(22, 110);
	wait_pid();
	set_turn_target(90, 100);
	wait_pid();
	set_drive_target(-31, 110);
	wait_pid();
	clamp.set_value(true);
	set_turn_target(-135, 100);
	wait_pid();
	set_drive_target(30, 110);
	wait_pid();
	set_turn_target(-90, 100);
	wait_pid();
	set_drive_target(21, 110);
	wait_pid();
	set_turn_target(-135, 100);
	wait_pid();
	set_drive_target(23, 110);
	wait_pid();
	set_turn_target(-190, 100);
	wait_pid();



}
void LeftSoloAWP(){

	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);


	
	set_drive_target(-21, 70);
	wait_pid();
	clamp.set_value(true);
	pros::delay(500);
	//clamp rush rings
	intake_front.move(95);
	intake_back.move(95);

	set_turn_target(142, 100);
	wait_pid();
	pros::delay(500);


	set_drive_target(27, 110);
	wait_pid();
	pros::delay(500);

	set_turn_target(115, 100);
	wait_pid();

	set_drive_target(8, 110);
	wait_pid();
	
	set_turn_target(-7, 100);
	wait_pid();

	set_drive_target(13, 110);
	wait_pid();

	set_turn_target(-7, 100);
	wait_pid();

	set_turn_target(-45, 100);
	wait_pid();
//This following movement is heading to the AWP stake
	set_drive_target(48, 110);
	wait_pid();


//bar
	set_turn_target(-155, 100);
	wait_pid();

	set_drive_target(50, 110);
	wait_pid();



}

void RightSoloAWP(){

	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);


	
	set_drive_target(-21, 70);
	wait_pid();
	clamp.set_value(true);
	pros::delay(500);
	//clamp rush rings
	intake_front.move(95);
	intake_back.move(95);

	set_turn_target(-142, 100);
	wait_pid();
	pros::delay(500);


	set_drive_target(27, 110);
	wait_pid();
	pros::delay(500);

	set_turn_target(-115, 100);
	wait_pid();

	set_drive_target(8, 110);
	wait_pid();
	
	set_turn_target(7, 100);
	wait_pid();

	set_drive_target(13, 110);
	wait_pid();

	set_turn_target(7, 100);
	wait_pid();

	set_turn_target(45, 100);
	wait_pid();
//This following movement is heading to the AWP stake
	set_drive_target(48, 110);
	wait_pid();


//bar
	set_turn_target(155, 100);
	wait_pid();

	set_drive_target(50, 110);
	wait_pid();



}


void DreadedAssFuckingCode(){

	set_drive_constants(0.2, 0.5, 10000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2500, 2, 1, 50);

	set_drive_target(120, 110);
	wait_pid();


}




/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	left_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    right_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);

	pros::Task pid_task(pid_thread);
	pros::Task odom_task(odom_thread);

	skills_auto();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Task odom_task(odom_thread);
	left_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    right_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);

	bool clamp_state = true;
	int last_clamp_change = 0;

	bool wall_stake_held = false;

	while (true) {
		pros::screen::print(TEXT_MEDIUM, 1, "X: %f", x);
		pros::screen::print(TEXT_MEDIUM, 2, "Y: %f", y);
		pros::screen::print(TEXT_MEDIUM, 3, "Rotation: %f", current_rotation);
		pros::screen::print(TEXT_MEDIUM, 4, "XTrack: %f", horizontal_encoder.get_position());
		pros::screen::print(TEXT_MEDIUM, 5, "YTrack: %f", vertical_encoder.get_position());
		drive();

		if (master.get_digital(DIGITAL_L1)) { // clamp
			if (pros::millis() - last_clamp_change > CLAMP_COOLDOWN) {
				clamp.set_value(clamp_state);
				clamp_state = !clamp_state;
				last_clamp_change = pros::millis();
			}
		}

		if (master.get_digital(DIGITAL_R1)) {
			intake_front.move(INTAKE_VOLTS);
			intake_back.move(INTAKE_VOLTS);
		} else if (master.get_digital(DIGITAL_R2)) {
			intake_front.move(-INTAKE_VOLTS);
			intake_back.move(-INTAKE_VOLTS);
		} else {
			intake_front.move(0);
			intake_back.move(0);
		}

		if (master.get_digital(DIGITAL_L2)) {
			wall_stake_held = true;
			wall_stake_motor.move(WALLSTAKE_VOLTS);
		} else if (wall_stake_held) {
			wall_stake_held = false;
			wall_stake_motor.move(0);
			wall_stake_motor.move_absolute(0, WALL_STAKE_RPM);
		}

		pros::delay(10);
	}
}