#include "main.h"
#include "include/autonomous.h"
#include "pros/misc.h"
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
	intake_front.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake_back.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	wall_stake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	imu1.reset();
	imu1.tare();
	imu2.reset();
	imu2.tare();

	while (imu1.is_calibrating() || imu2.is_calibrating()) {
		pros::delay(10);
	}

	imu1.set_rotation(init_angle);
	imu2.set_rotation(init_angle);
	imu1.set_heading(init_angle);
	imu2.set_heading(init_angle);

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
	pid_enabled = false;
	pros::Task odom_task(odom_thread);
	left_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    right_drive.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);

	bool clamp_state = true;
	int last_clamp_change = 0;

	int last_l2 = 0;

	bool doinker_state = true;
	int last_doinker_change = 0;

	while (true) {
		drive();

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

		// colour sorter
		/*colour.set_led_pwm(100);
		if (colour.get_rgb().red > 1000 && distance.get_distance() < 60) {
			getting_rid_of_ring = true;
			pros::Task get_rid_of_ring([] {
				double target = wall_stake_encoder.get_position() + 36000;
				double error = wall_stake_encoder.get_position() - target;
				while (fabs(error) > 1000) {
					error = wall_stake_encoder.get_position() - target;
					wall_stake_motor.move(error * 0.002); // arm kp colour = 0.002
					pros::delay(10);
				}
				wall_stake_motor.move(0);
				getting_rid_of_ring = false;
			});
		}*/

		if ((master.get_digital(DIGITAL_R1)) && (l2_mode == 0 || (l2_mode == 2 && wall_stake_holding) || l2_mode == 3 || (l2_mode == 1 && distance.get_distance() > 60)) && (!getting_rid_of_ring)) {
			intake_front.move(INTAKE_VOLTS);
			intake_back.move(INTAKE_VOLTS);
		} else if (master.get_digital(DIGITAL_R2)) {
			intake_front.move(-INTAKE_VOLTS);
			intake_back.move(-INTAKE_VOLTS);
		} else {
			intake_front.move(0);
			intake_back.move(0);
		}

		if (l2_mode == 1 && distance.get_distance() < 60) {
			l2_mode = 2;
			pros::Task delay_task([] {
				pros::delay(500);
				pros::Task([] {
					wall_stake_motor.move_relative(-1100, WALL_STAKE_RPM);
					int i = 0;
					double start_pos = wall_stake_motor.get_position();
					while ((fabs(wall_stake_motor.get_position() - start_pos + 1100) < 50) && (i < 100)) {
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
		}

		/*if (master.get_digital(DIGITAL_L2)) {
			wall_stake_held = true;
			wall_stake_motor.move(-WALLSTAKE_VOLTS);
			last_wall_stake_auto = pros::millis();
		} else if (wall_stake_held) {
			wall_stake_held = false;
			wall_stake_motor.move(0);
			wall_stake_motor.move_absolute(0, WALL_STAKE_RPM);
		}*/

		if (master.get_digital(DIGITAL_L2)) {
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
		}

		if (master.get_digital(DIGITAL_X) && l2_mode == 0 && pros::millis() - last_l2 > WALL_STAKE_COOLDOWN) {
			wall_stake_motor.move(-WALLSTAKE_VOLTS);
		} else if (master.get_digital(DIGITAL_B) && l2_mode == 0 && pros::millis() - last_l2 > WALL_STAKE_COOLDOWN) {
			wall_stake_motor.move(WALLSTAKE_VOLTS);
		} else if (l2_mode == 0 && pros::millis() - last_l2 > WALL_STAKE_COOLDOWN) {
		 	wall_stake_motor.move(0);
		}

		pros::delay(10);
	}
}

