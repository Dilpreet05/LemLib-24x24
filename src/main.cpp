#include "main.h"
#include "liblvgl/llemu.hpp"
#include "liblvgl/lvgl.h" // IWYU pragma: keep
#include "liblvgl/llemu.h" // IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

// #include "asset.h"

// ASSET(hot_chip_gif)
// ASSET(chip_gif)
// ASSET(spongebob_gif)
// ASSET(test_txt)


void initialize()
{
    
    console.focus();
    console.printf("Initializing...\n");
    chassis.calibrate(); // calibrate sensors
    setBrakes();
    // pros::lcd::initialize(); // initialize brain screen
    console.printf("Done.\nGoing to selector.");
    pros::delay(250);

    selector.focus();

    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
			console.printf("X: %f\n", chassis.getPose().x);
			console.printf("Y: %f\n",chassis.getPose().y);
			console.printf("Theta: %f\n", chassis.getPose().theta);
            console.printf("Hook_Motor mA draw: %d\nHook_Motor power draw: %lf\nHook_Motor efficiency: %lf",hookIntakeMotor.get_current_draw(),hookIntakeMotor.get_power(),hookIntakeMotor.get_efficiency());


            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

            // delay to save resources
            pros::delay(50);
			console.clear();
        }
    });


}

/**
 ** Runs while the robot is in the disabled state of Field Management System or
 ** the VEX Competition Switch, following either autonomous or opcontrol. When
 ** the robot is enabled, this task will exit.
 */
void disabled()
{

    // This displays a funny gif on our brain while our robot is in the disabled state.
    // psychlogical warfare against our opposing teams.
}

/**
 ** Runs after initialize(), and before autonomous when connected to the Field
 ** Management System or the VEX Competition Switch. This is intended for
 ** competition-specific initialization routines, such as an autonomous selector
 ** on the LCD.
 *
 ** This task will exit when the robot is enabled and autonomous or opcontrol
 ** starts.
 */
void competition_initialize() {}

/**
 ** Runs the user autonomous code. This function will be started in its own task
 ** with the default priority and stack size whenever the robot is enabled via
 ** the Field Management System or the VEX Competition Switch in the autonomous
 ** mode. Alternatively, this function may be called in initialize or opcontrol
 ** for non-competition testing purposes.
 *
 ** If the robot is disabled or communications is lost, the autonomous task
 ** will be stopped. Re-enabling the robot will restart the task, not re-start it
 ** from where it left off.
 */
void autonomous()
{
    intake_stuck_task.suspend();
    stickMotor.tare_position();
    stakeMotor.tare_position();


    console.focus();
    selector.run_auton();


}

/**
 ** Runs the operator control code. This function will be started in its own task
 ** with the default priority and stack size whenever the robot is enabled via
 ** the Field Management System or the VEX Competition Switch in the operator
 ** control mode.
 *
 ** If no competition control is connected, this function will run immediately
 ** following initialize().
 *
 ** If the robot is disabled or communications is lost, the
 ** operator control task will be stopped. Re-enabling the robot will restart the
 ** task, not resume it from where it left off.
 */

void opcontrol()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    while (true)
    {
        chassisControl();
        intakeControl();
        moveStakeMech();
        updateClamp();
        stickControl();
        pros::delay(25);
    }
}