#include "main.h"
#include "liblvgl/llemu.hpp"
#include "liblvgl/lvgl.h" // IWYU pragma: keep
#include "liblvgl/llemu.h" // IWYU pragma: keep

// #include "asset.h"

// ASSET(hot_chip_gif)
// ASSET(chip_gif)
// ASSET(spongebob_gif)
ASSET(test_txt)

void initialize()
{
    pros::lcd::initialize(); // initialize brain screen
    // pros::lcd::clear();

    // gif = new Gif(chip_gif,lv_scr_act());

    // pros::delay(2000);
    chassis.calibrate(); // calibrate sensors
    setBrakes();

    // pros::Task gifTask([&](){

    //     gif = new Gif(hot_chip_gif,lv_scr_act());

    // });

    // print position to brain screen

    // pros::Task screen_task([&]()
    //                        {
    //     while (true) {
    //         // print robot location to the brain screen
    //         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    //         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    //         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
    //         // delay to save resources
    //         pros::delay(20);
    //     } });
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
    chassis.setPose(0, 0, 0);
    chassis.follow(test_txt, 15, 20000);
    chassis.waitUntilDone();
    // chassis.moveToPoint(0, 24, 40000);
    // pros::lcd::clear();
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
    int frame = 0;
    while (true)
    {
        frame++;
        // chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
        chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        intakeControl();
        moveStakeMech();
        updateClamp();
        stickControl();
        check_motors_and_get_temps();
    }
}