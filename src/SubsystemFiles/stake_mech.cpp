#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include <cstdint>

pros::Motor stakeMotor(11, pros::MotorGearset::green, pros::MotorUnits::degrees);
pros::adi::DigitalOut leftSide('H', LOW);
pros::adi::DigitalOut rightSide('G', LOW);
bool pistonState = false;

void moveStakeMech()
{
    // Move stake motor while holding y
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
        stakeMotor.move(127);
    }

    // Move stake motor the other way while holding B
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    {
        stakeMotor.move(-127);
    }

    // Stop otherwise
    else
    {
        stakeMotor.brake();
    }

    // Press DOWN to toggle the left and right pistons
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
        pistonState = !pistonState;
        leftSide.set_value(pistonState);
        rightSide.set_value(pistonState);
    }
}

void setStakeMotorBrake()
{
    // Set brake to prevent accidental movement of stake motor (gravity, inertia, etc)
    stakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}