#include "main.h"

pros::Motor stickMotor(5, pros::MotorGearset::green, pros::v5::MotorUnits::degrees);

/**
 * 
 * 
 * 
 */
void stickControl()
{
    if (master.get_digital(DIGITAL_RIGHT))
    {
        stickMotor.move(127);
    }
    else if (master.get_digital(DIGITAL_DOWN))
    {
        stickMotor.move(-127);
    }
    else
    {
        stickMotor.brake();
    }
}

void setStickBrakes()
{
    stickMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
}