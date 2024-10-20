#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/rtos.hpp"

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

ASSET(path1_txt)

void redRightSide()
{

    chassis.setPose(-61.287,-32.171,270);

    chassis.moveToPoint(-32, -32.171, 1200, {.forwards = false, .maxSpeed = 100}, false);

    chassis.turnToPoint(-24, -24, 500, {.forwards = false});
    liftMove(1);

    chassis.moveToPoint(-18, -18, 1200,{.forwards=false,.minSpeed=90});
    chassis.waitUntil(10);
    clampDown();

    // chassis.moveToPoint(-55, -11.054, 750,{.forwards=false});

    // chassis.swingToPoint(-24, -24, DriveSide::RIGHT, 750,{.forwards=false});

    // chassis.moveToPoint(-24, -24, 1500,{.forwards=false,.minSpeed=100});
    // clampDown();

    chassis.moveToPoint(-24, -54, 2000,{.minSpeed=70});
    intake();
    
    chassis.moveToPoint(-24, -50, 500,{.forwards=false,.minSpeed=127},false);
    chassis.moveToPoint(-24, -58, 500,{.forwards=false,.minSpeed=127},false);
    chassis.moveToPoint(-24, -50, 500,{.forwards=false,.minSpeed=127},false);
    chassis.moveToPoint(-24, -58, 500,{.forwards=false,.minSpeed=127},false);

    pros::delay(1500);
    stopIntake();

    chassis.moveToPoint(-38, -48, 2000,{.forwards=false,.minSpeed=50},false);
    stopIntake();
    clampUp();

    // chassis.moveToPoint(-2,-48,2000,{.forwards=false,.minSpeed=120},false);
    // clampDown();

    chassis.moveToPoint(-18, -18, 1500,{.minSpeed=20},false);
    chassis.turnToPoint(-17, -17, 500);

    stakeMotor.move(-100);
    pros::delay(1000);
    stakeMotor.brake();



}

void bottomRush(int color){
    // 1 for red, -1 for blue

    chassis.setPose(-58,-30,270);

    chassis.moveToPoint(-24*color,  -30, 1500,{.forwards=false});
    chassis.turnToPoint(-10*color, -36,1000,{.forwards=false});
    chassis.moveToPoint(-10*color, -36, 1500,{.forwards=false});
    stakeMotor.move_absolute(-200, 127);
    chassis.waitUntil(5);

    stickMotor.move_relative(-125, 127);

    chassis.moveToPoint(-10-20*color, -33+20, 1500);

}