#include "lemlib/pid.hpp"
#include "main.h"

pros::Motor stakeMotor(11, pros::MotorGearset::green, pros::MotorUnits::degrees);


void moveStakeMech()
{

    // if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    // {
    //     stakeMotor.move_absolute(0, 127);
    // }
    // else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    // {
    //     stakeMotor.move_absolute(367, 127);
    // }
    // else
    // {
    //     stakeMotor.brake();
    // }

    if (master.get_digital_new_press(DIGITAL_L1))
    {
        liftMove(1);
    }
    else if (master.get_digital_new_press(DIGITAL_L2))
    {
        liftMove(0);
    }

}

void setStakeMotorBrake()
{
    // Set brake to prevent accidental movement of stake motor (gravity, inertia, etc)
    stakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}