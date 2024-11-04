#include "main.h"

/* Start of Intake Code */

// Placeholder motor ports.
pros::Motor flexWheelIntakeMotor(20, pros::MotorGearset::green, pros::v5::MotorUnits::degrees);
pros::Motor hookIntakeMotor(12, pros::MotorGearset::red, pros::v5::MotorUnits::degrees);

int fast_hook_intake_speed = 127;
int slow_hook_intake_speed = 118;
int super_slow_intake_speed = 60;
int hook_intake_speed = fast_hook_intake_speed;

void intakeControl()
{
    // Outtake while holding R2
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        hookIntakeMotor.move(hook_intake_speed);
        flexWheelIntakeMotor.move(127);
    }

    // Intake while holding R1
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) )
    {
        hookIntakeMotor.move(-hook_intake_speed);
        flexWheelIntakeMotor.move(-127);
    }

    // Stop otherwise
    else
    {
        hookIntakeMotor.brake();
        flexWheelIntakeMotor.brake();
    }

    // Swap the hook intake speed
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        hook_intake_speed = (hook_intake_speed == fast_hook_intake_speed) ? slow_hook_intake_speed : fast_hook_intake_speed;
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
        hook_intake_speed = super_slow_intake_speed;
    }
}

void setIntakeBrakes()
{
    // Set the intake motors to break with coast
    flexWheelIntakeMotor.set_brake_mode(pros::MotorBrake::coast);
    hookIntakeMotor.set_brake_mode(pros::MotorBrake::coast);
}

/* End of Intake Code */