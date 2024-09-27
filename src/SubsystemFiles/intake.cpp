#include "main.h"

/* Start of Intake Code */

// Placeholder motor ports.
pros::Motor flexWheelIntakeMotor(20, pros::MotorGearset::green, pros::v5::MotorUnits::degrees);
pros::Motor hookIntakeMotor(12, pros::MotorGearset::green, pros::v5::MotorUnits::degrees);

void intakeControl()
{
    // Move hook intake while holding R1
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        hookIntakeMotor.move(127);
        flexWheelIntakeMotor.move(127);
    }

    // Move hook intake the other way while holding R2
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        flexWheelIntakeMotor.move(-127);
        hookIntakeMotor.move(-127);
    }

    // Stop otherwise
    else
    {
        hookIntakeMotor.brake();
        flexWheelIntakeMotor.brake();
    }
}

void setIntakeBrakes()
{
    // Set the intake motors to break with coast
    flexWheelIntakeMotor.set_brake_mode(pros::MotorBrake::coast);
    hookIntakeMotor.set_brake_mode(pros::MotorBrake::coast);
}

/* End of Intake Code */