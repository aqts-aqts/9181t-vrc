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
	wall_stake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	imu1.reset();
	imu1.tare();
	imu2.reset();
	imu2.tare();
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
/*
void awp_blue() {
	set_drive_target(-33, 70);
	wait_pid();

	clamp.set_value(1);

	pros::delay(500);

	set_drive_target(11, 70);
	wait_pid();

	intake.move(127);

	pros::delay(2000);

	set_drive_target(-18, 70); // -22
	wait_pid();

	set_turn_target(-90, 100); //-90
	wait_pid();

	set_drive_target(30, 100);
	wait_pid();

	pros::delay(1500);
	
	set_drive_target(-5, 100);
	wait_pid();

	intake.move(127);

	set_turn_target(-180, 100); // -180
	wait_pid();

	set_drive_target(16, 70); // 12
	wait_pid();

	set_drive_target(-8, 70);
	wait_pid();

	set_turn_target(-145, 127); //155
	wait_pid();

	set_drive_target(15, 100);
	wait_pid();

	set_drive_target(-5, 100);
	wait_pid();

	set_turn_target(-250, 100); // -270
	wait_pid();

	set_drive_target(20, 100);
	wait_pid();

	set_turn_target(-220, 100);
	wait_pid();

	set_drive_target(8, 100);
	wait_pid();
}
*/

void test(){
	set_turn_target(90, 100);
	wait_pid();

	set_turn_target(0, 100);
	wait_pid();
}

void awp_right() {
	set_drive_target(-32, 70);
	wait_pid();

	//clamp.set_value(1);

	pros::delay(500);

	set_drive_target(10, 70);
	wait_pid();

	//intake.move(127);

	pros::delay(2000);

	set_drive_target(-18, 70); // -22
	wait_pid();

	set_turn_target(-90, 100); //-90
	wait_pid();

	set_drive_target(30, 100);
	wait_pid();

	pros::delay(1500);
	
	//set_drive_target(-5, 100);
	//wait_pid();

	//intake.move(127);

	set_turn_target(-180, 100); // -180
	wait_pid();

	set_drive_target(18, 70); // 12
	wait_pid();

	set_drive_target(-8, 70);
	wait_pid();

	set_turn_target(-145, 127); //155
	wait_pid();

	set_drive_target(15, 100);
	wait_pid();

	set_drive_target(-5, 100);
	wait_pid();

	set_turn_target(-300, 100); // -270
	wait_pid();

	set_drive_target(20, 100);
	wait_pid();

	set_turn_target(-220, 100);
	wait_pid();

	set_drive_target(20, 100);
	wait_pid();

	//intake.move(0);
}

void awp_left() {
	set_drive_target(-37, 40);
	wait_pid();

	//clamp.set_value(1);

	pros::delay(500);

	set_drive_target(15, 70);
	wait_pid();

	//intake.move(127);

	pros::delay(2000);

	set_drive_target(-18, 70); // -22
	wait_pid();

	set_turn_target(90, 100); //90
	wait_pid();

	set_drive_target(30, 100);
	wait_pid();

	pros::delay(1500);
	
	//set_drive_target(-5, 100);
	//wait_pid();

	//intake.move(127);

	set_turn_target(180, 100); // -180
	wait_pid();

	set_drive_target(18, 70); // 12
	wait_pid();

	set_drive_target(-8, 70);
	wait_pid();

	set_turn_target(145, 127); //155
	wait_pid();

	set_drive_target(15, 100);
	wait_pid();

	set_drive_target(-5, 100);
	wait_pid();

	set_turn_target(300, 100);
	wait_pid();

	set_drive_target(20, 100);
	wait_pid();

	set_turn_target(220, 100);
	wait_pid();

	set_drive_target(25, 100);
	wait_pid();

	//intake.move(0);
}

/*
void awp_red() {
	set_drive_target(-33, 70);
	wait_pid();

	clamp.set_value(1);

	pros::delay(500);

	set_drive_target(11, 70);
	wait_pid();

	intake.move(127);

	pros::delay(2000);

	set_drive_target(-18, 70); // -22
	wait_pid();

	set_turn_target(90, 100, 1.1, 0.5, 0.002); //-90
	wait_pid();

	set_drive_target(30, 100);
	wait_pid();

	pros::delay(1500);
	
	set_drive_target(-5, 100);
	wait_pid();

	intake.move(127);

	set_turn_target(180, 100); // -180
	wait_pid();

	set_drive_target(16, 70); // 12
	wait_pid();

	set_drive_target(-8, 70);
	wait_pid();

	set_turn_target(145, 127, 6, 0.5, 0.014); //155
	wait_pid();

	set_drive_target(15, 100);
	wait_pid();

	set_drive_target(-5, 100);
	wait_pid();

	set_turn_target(250, 100, 1.5, 0.5, 0.003); // -270
	wait_pid();

	set_drive_target(20, 100);
	wait_pid();

	set_turn_target(220, 100);
	wait_pid();

	set_drive_target(8, 100);
	wait_pid();
}*/

void go_straight() {
	set_drive_target(20, 100);
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
	left_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    right_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);

	pros::Task pid_task(pid_thread);
	pros::Task odom_task(odom_thread);

	awp_left();
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
	left_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    right_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);

	bool clamp_state = false;
	int last_clamp_change = 0;

	int wall_stake_pos = 0;
	int last_wall_stake_change = 0;

	while (true) {
		drive();

		if (master.get_digital(DIGITAL_L1)) { // clamp
			if (pros::millis() - last_clamp_change > CLAMP_COOLDOWN) {
				clamp_state = !clamp_state;
				clamp1.set_value(clamp_state);
				clamp2.set_value(clamp_state);
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
			if (pros::millis() - last_wall_stake_change > WALL_STAKE_COOLDOWN) {
				wall_stake_pos = (wall_stake_pos == 0) ? -420: 0;
				wall_stake_motor.move_absolute(wall_stake_pos, WALL_STAKE_RPM);
				last_wall_stake_change = pros::millis();
			}
		}

		pros::delay(10);
	}
}