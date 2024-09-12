#include "main.h"


/* Start of Intake Code */

// placeholder motor ports.
pros::Motor flexWheelIntakeMotor(-10, pros::MotorGearset::green, pros::v5::MotorUnits::degrees);
pros::Motor hookIntakeMotor(-11, pros::MotorGearset::green, pros::v5::MotorUnits::degrees);

void intakeControl()
{

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    { // Move wheel intake while holding L1
        flexWheelIntakeMotor.move(127);
    }
    else
    { // Stop wheel intake otherwise
        flexWheelIntakeMotor.move(0);
        flexWheelIntakeMotor.brake();
    }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    { // Move hook intake while holding R1
        hookIntakeMotor.move(127);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    { // Move hook intake the other way while holding L2
        hookIntakeMotor.move(-127);
    }
    else
    { // Stop otherwise
        hookIntakeMotor.move(0);
        hookIntakeMotor.brake();
    }
}

void setIntakeBrakes()
{ // Set the intake motors to break with coast

    flexWheelIntakeMotor.set_brake_mode(pros::MotorBrake::coast);
    hookIntakeMotor.set_brake_mode(pros::MotorBrake::coast);
}

/* End of Intake Code */