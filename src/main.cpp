#include "main.h"
#include "include/autonomous.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
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
	wall_stake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	imu1.reset();
	imu1.tare();
	imu2.reset();
	imu2.tare();

	while (imu1.is_calibrating() || imu2.is_calibrating()) {
		pros::delay(10);
	}

	imu1.set_rotation(inital_angle);
	imu2.set_rotation(inital_angle);
	imu1.set_heading(inital_angle);
	imu2.set_heading(inital_angle);

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

	set_drive_constants(0.2, 0.5, 4000, 20, 10, 50);
	set_turn_constants(4.2, 0.01, 40, 45, 2000, 2, 1, 50);

	skills();
	//BlueRingSideProvis();
	//awpBlue();
	//awpRed();
	//soloAwpBlue();
	//soloAwpRed();
	//RedRingSideProvis();
	

	// in device.cpp, for matches switch inital_angle to 90!! leave at 297 for skills
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
	intake_running = false;
	colour_sorted = true;
	pid_enabled = false;
	pros::Task odom_task(odom_thread);
	left_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    right_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);

	bool clamp_state = true;
	int last_clamp_change = 0;

	int last_l2 = 0;
	bool y_toggle = false;
	int last_y = 0;

	bool doinker_state = true;
	int last_doinker_change = 0;

	bool wall_stake_held = false;
	int last_wall_stake_auto = 0;

	bool wall_stake_up = false;
	int last_wall_stake_up = 0;

	int intake_speed = INTAKE_VOLTS;
	int last_seen = 0;

	holding = true;
	holding_up = false;

	while (true) {
		drive();

		if (holding && !holding_up && fabs(wall_stake_motor.get_position()) > 25)
			wall_stake_motor.move(-wall_stake_motor.get_position() * 0.2); // kp = 0.2

		if (master.get_digital(DIGITAL_L1)) { // clamp
			if (pros::millis() - last_clamp_change > CLAMP_COOLDOWN) {
				clamp.set_value(clamp_state);
				clamp_state = !clamp_state;
				last_clamp_change = pros::millis();
			}
		}

		if (master.get_digital(DIGITAL_A)) { // doinker
			if (pros::millis() - last_doinker_change > DOINKER_COOLDOWN) {
				doinker.set_value(doinker_state);
				doinker_state = !doinker_state;
				last_doinker_change = pros::millis();
			}
		}

		if (y_toggle && distance.get_distance() < 90) {
			last_seen = pros::millis();
		}

		//if ((master.get_digital(DIGITAL_R1)) && (l2_mode == 0 || (l2_mode == 2 && wall_stake_holding) || l2_mode == 3 || (l2_mode == 1 && distance.get_distance() > 60)) && (!getting_rid_of_ring)) {
		if (master.get_digital(DIGITAL_R1) && (!y_toggle || pros::millis() - last_seen > 500)) {
			intake_front.move(intake_speed);
			intake_back.move(intake_speed);
		} else if (master.get_digital(DIGITAL_R2)) {
			intake_front.move(-intake_speed);
			intake_back.move(-intake_speed);
		} else {
			intake_front.move(0);
			intake_back.move(0);
		}

		if (master.get_digital(DIGITAL_UP) && pros::millis() - last_wall_stake_up > 500) {
			if (!wall_stake_up) {
				holding_up = true;
				wall_stake_motor.move(0);
				wall_stake_motor.move_relative(-1200, WALL_STAKE_RPM-40);
			} else {
				double distance = fmod(wall_stake_motor.get_position(), 2700);
				wall_stake_motor.move(0);
				wall_stake_motor.move_relative(-2700 - distance, WALL_STAKE_RPM-40);
				pros::Task([] {
					pros::delay(1000);
					wall_stake_motor.tare_position();
					holding_up = false;
				});
			}
			wall_stake_up = !wall_stake_up;
			last_wall_stake_up = pros::millis();
		}

		/*if (l2_mode == 1 && distance.get_distance() < 60) {
			l2_mode = 2;
			pros::Task delay_task([] {
				pros::delay(500);
				pros::Task([] {
					wall_stake_motor.move_relative(-1100, WALL_STAKE_RPM);
					int i = 0;
					double start_pos = wall_stake_motor.get_position();
					while ((fabs(wall_stake_motor.get_position() - start_pos + 31100) < 50) && (i < 100)) {
						pros::delay(10);
						i++;
					}
					wall_stake_holding = true;
					if (i >= 100) { // rotate arm until back to inital pos
						while (fabs(fmod(wall_stake_encoder.get_position(), 36000)) > 1000) {
							double error = fmod(wall_stake_encoder.get_position(), 36000);
							wall_stake_motor.move(error * 0.0006); // arm kp = 0.0006
							pros::delay(10);
						}
						wall_stake_motor.move(0);
						l2_mode = 0;
						wall_stake_holding = false;
					}
				});
			});
		}*/
		
		if (master.get_digital(DIGITAL_Y) && pros::millis() - last_y > 500) {
			y_toggle = !y_toggle;
			intake_speed = y_toggle ? INTAKE_VOLTS : INTAKE_VOLTS;
			last_y = pros::millis();
		}


		if (master.get_digital(DIGITAL_L2)) {
			wall_stake_held = true;
			holding = false;
			wall_stake_motor.move(-WALLSTAKE_VOLTS);
			last_wall_stake_auto = pros::millis();
		} else if (wall_stake_held) {
			wall_stake_held = false;
			wall_stake_motor.move_absolute(0, WALL_STAKE_RPM);
			pros::Task([] {
				while (fabs(wall_stake_motor.get_position()) > 50) {
					pros::delay(10);
				}
				holding = true;
			});
		}

		/*if (master.get_digital(DIGITAL_L2)) {
			if (l2_mode == 0) {
				l2_mode = 1;
				last_l2 = pros::millis();
			} else if (l2_mode == 2 && pros::millis() - last_l2 > WALL_STAKE_COOLDOWN) {
				l2_mode = 3;
				wall_stake_holding = false;
				last_l2 = pros::millis();
				wall_stake_motor.move(-WALLSTAKE_VOLTS);
			}
		} else if (l2_mode == 3) {
			l2_mode = 0;
			last_l2 = pros::millis();
			pros::Task([] {
				while (fabs(fmod(wall_stake_encoder.get_position(), 36000)) > 1000) {
					double error = fmod(wall_stake_encoder.get_position(), 36000);
					wall_stake_motor.move(-error * 0.0006); // arm kp = 0.0006
					pros::delay(10);
				}
				wall_stake_motor.move(0);
			});
		}*/

		/*if (master.get_digital(DIGITAL_X) && l2_mode == 0 && pros::millis() - last_l2 > WALL_STAKE_COOLDOWN) {
			wall_stake_motor.move(-WALLSTAKE_VOLTS);
		} else if (master.get_digital(DIGITAL_B) && l2_mode == 0 && pros::millis() - last_l2 > WALL_STAKE_COOLDOWN) {
			wall_stake_motor.move(WALLSTAKE_VOLTS);
		} else if (l2_mode == 0 && pros::millis() - last_l2 > WALL_STAKE_COOLDOWN) {
		 	wall_stake_motor.move(0);
		}*/

		if (master.get_digital(DIGITAL_B) && pros::millis() - last_wall_stake_auto > WALL_STAKE_COOLDOWN && !holding_up) {
			holding = false;
			wall_stake_motor.move(-WALLSTAKE_VOLTS);
		} else if (master.get_digital(DIGITAL_DOWN) && pros::millis() - last_wall_stake_auto > WALL_STAKE_COOLDOWN && !holding_up) {
			holding = false;
			wall_stake_motor.move(WALLSTAKE_VOLTS);
		} else if (pros::millis() - last_wall_stake_auto > WALL_STAKE_COOLDOWN && !holding && !holding_up) {
			holding = true;
		 	wall_stake_motor.move(0);
			wall_stake_motor.tare_position();
		}

		pros::delay(10);
	}
}