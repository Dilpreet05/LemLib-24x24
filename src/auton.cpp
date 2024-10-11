#include "main.h" // IWYU pragma: keep

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

void stopIntake(){
    hookIntakeMotor.move(0);
    flexWheelIntakeMotor.move(0);    
}

void liftMove(int n){
    
    if(n=0){
        // downwards position
        stakeMotor.move_absolute(0,127);
    }else if(n=1){
        // upwards position
        stakeMotor.move_absolute(-200,127);
    }else if(n=2){
        // score position AND position for AWP Ladder touch.
        stakeMotor.move_absolute(-300,127);
    }

}

ASSET(path1_txt)

void redRightSide(){

    chassis.setPose(-61.696,-32.171,270);

    chassis.moveToPoint(-32, -32.171, 1200,{.forwards=false,.maxSpeed=100},false);

    chassis.turnToPoint(-24,-24,500,{.forwards=false});
    liftMove(1);

    chassis.moveToPoint(-18, -18, 700,{.forwards=false,.minSpeed=90});
    chassis.waitUntil(10);
    clampDown();

    chassis.moveToPoint(-24, -54, 1250,{.minSpeed=70});
    intake();

    pros::delay(2500);
    stopIntake();

    chassis.moveToPoint(-38, -48, 1500,{.forwards=false,.minSpeed=100},false);
    stopIntake();
    clampUp();

    // chassis.moveToPoint(-2,-48,2000,{.forwards=false,.minSpeed=120},false);
    // clampDown();

    // chassis.moveToPose(-15, -15, 45,1500,{.lead=8},false);
    // liftMove(3);




}