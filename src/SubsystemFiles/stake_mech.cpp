#include "lemlib/pid.hpp"
#include "main.h"

pros::Motor stakeMotor(11, pros::MotorGearset::green, pros::MotorUnits::degrees);

int speed = 127;

lemlib::PID stakePID(5,0,20,0,false);

void moveStakeMech()
{

    // Move stake motor while holding y
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
        stakeMotor.move_absolute(0, 127);
    }

    // Move stake motor the other way while holding B
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    {
        stakeMotor.move_absolute(367, 127);
    }

    // Stop otherwise
    else
    {
        stakeMotor.brake();
    }


}

void setStakeMotorBrake()
{
    // Set brake to prevent accidental movement of stake motor (gravity, inertia, etc)
    stakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}