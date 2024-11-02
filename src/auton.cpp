#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/rtos.hpp"
ASSET(corner_txt)

/* Tuning Functions */

// tune kP and kD
void tuneAngularPID()
{
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(90, 10000);
}

void tuneLinearPID()
{
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 48, 10000);
}

/* Subsystems */
int intakeSpeed = 127;

void clampDown()
{
    leftClampPiston.set_value(1);
    rightClampPiston.set_value(1);
}

void clampUp()
{
    leftClampPiston.set_value(0);
    rightClampPiston.set_value(0);
}
int desiredHookIntakeSpeed = 0;
void intake()
{
    desiredHookIntakeSpeed = -intakeSpeed;
    hookIntakeMotor.move(-intakeSpeed);
    flexWheelIntakeMotor.move(-127);
}

void outtake()
{
    desiredHookIntakeSpeed = intakeSpeed;
    hookIntakeMotor.move(intakeSpeed);
    flexWheelIntakeMotor.move(127);
}

void stopIntake()
{
    desiredHookIntakeSpeed = 0;
    hookIntakeMotor.move(0);
    flexWheelIntakeMotor.move(0);
}

void liftMove(int n)
{

    if (n == 0)
    {
        // downwards position
        stakeMotor.move_absolute(0, 127);
    }
    else if (n == 1)
    {
        // upwards position
        stakeMotor.move_absolute(-200, 127);
    }
    else if (n == 2)
    {
        // score position AND position for AWP Ladder touch.
        stakeMotor.move_absolute(-300,127);
    }else{
        stakeMotor.move_absolute(-500, 80);
    }
}

void stickMove(int n){
    if(n==1){
        stickMotor.move_absolute(-400, 127);
    }else{
        stickMotor.move_absolute(0, 127);
    }
}


void intakeTask(void* parameter)
{
    // Spits out ring if its the wrong color
    // Otherwise it acts normally
    while (true)
    {
        if (ring_is_red())
        // if (ring_is_blue())
        {
            hookIntakeMotor.move(-127);
            pros::delay(1250);
        }
        else
        {
            hookIntakeMotor.move(desiredHookIntakeSpeed);
        }
    }
}




/* match autons */

void redTopRush(){
    chassis.setPose(-52,32,270);


    chassis.moveToPose(-15, 45, 210, 3000,{.forwards=false,.lead=.5,.minSpeed=70},false);  

    stickMotor.move(- 127);
    pros::delay(500);

    chassis.moveToPoint(-48, 24, 1750,{.maxSpeed=80},false);
    stickMotor.move_absolute(0, 127);

    chassis.moveToPose(-35, 30, 270, 2000,{.forwards=false},false);
    clampDown();

}



/* skills */

void skills(){

    chassis.setPose(-52,32,270);

    chassis.moveToPose(-24, 48, 220, 2500,{.forwards=false,.lead=.3,.minSpeed=60,.earlyExitRange=6});
    chassis.waitUntilDone();
    clampDown();
    stakeMotor.move_absolute(200, 70);

    chassis.turnToPoint(-24, 24, 750);
    chassis.moveToPoint(-24, 24, 1500);
    intake();
    chassis.moveToPoint(-24, 12, 2500,{.maxSpeed=40});


    chassis.turnToPoint(-48, 48, 750);
    chassis.moveToPoint(-48, 48, 2000);
    chassis.waitUntilDone();


    // chassis.moveToPoint(-60, 60, 2500,{},false);

    // pros::delay(2000);



    chassis.moveToPoint(-50, 50, 1000,{.forwards=true},false);
    pros::delay(2000);
    chassis.turnToPoint(-60, 60, 750,{.forwards=false});
    chassis.moveToPoint(-60, 60, 1500,{.forwards=false},false);
    outtake();
    clampUp();



    chassis.moveToPoint(0, 60, 3000);
    chassis.waitUntil(15);
    intake();
    // stopIntake();
    stakeMotor.move_absolute(0, 70);

    pros::delay(3000);
    stopIntake();
    stakeMotor.move_absolute(250, 80);

}