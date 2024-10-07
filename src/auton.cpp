#include "main.h" // IWYU pragma: keep
int hook_intake_speed = 127;

void clampDown(){
    leftClampPiston.set_value(1);
    rightClampPiston.set_value(1);
}

void clampUp(){
    leftClampPiston.set_value(0);
    rightClampPiston.set_value(0);
}

void intake(){
        hookIntakeMotor.move(-hook_intake_speed);
        flexWheelIntakeMotor.move(-127);
}

void outtake(){
    hookIntakeMotor.move(hook_intake_speed);
    flexWheelIntakeMotor.move(127);
}