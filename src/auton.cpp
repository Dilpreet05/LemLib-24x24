#include "main.h" // IWYU pragma: keep
#include "pros/llemu.hpp"

/* Tuning Functions */

// tune kP and kD
void tuneAngularPID(){
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(90, 10000);
}




void tuneLinearPID(){
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 48, 10000);
}



/* Subsystems */
int intakeSpeed = 127;

void clampDown(){
    leftClampPiston.set_value(1);
    rightClampPiston.set_value(1);
}

void clampUp(){
    leftClampPiston.set_value(0);
    rightClampPiston.set_value(0);
}

void intake(){
        hookIntakeMotor.move(-intakeSpeed);
        flexWheelIntakeMotor.move(-127);
}

void outtake(){
    hookIntakeMotor.move(intakeSpeed);
    flexWheelIntakeMotor.move(127);
}