#include "main.h"
#include "pros/misc.h"

pros::Motor stakeMotor(11, pros::MotorGearset::green, pros::MotorUnits::degrees);


void moveStakeMech()
{

    if (master.get_digital(DIGITAL_L2))
    {
        stakeMotor.move_absolute(0, 127);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        stakeMotor.move_absolute(367, 127);
    }
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