#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: keep
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
ASSET(SkillsPath_1_txt);


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


void findStartingPose(){
    chassis.setPose(0,48,270);
}


pros::Task intake_stuck_task([]{

    while(true){
        if (pros::Task::current().notify_take(true, 20)) {
            intakeStuckTaskOn = !intakeStuckTaskOn;
        }

        if(intakeStuckTaskOn && hookIntakeMotor.get_efficiency()<5 && hookIntakeMotor.get_actual_velocity()<0){
            outtake();
            pros::delay(250);
            intake();
        }
        pros::delay(20);
    }

});


/* match autons */

void experiment(){
    chassis.setPose(-43,32,270);

    stickMotor.move_absolute(75,70);
    chassis.moveToPoint(-11, 46, 1750,{.forwards=false,.minSpeed=80,.earlyExitRange=10},false);
    stickMotor.move(-127);
    pros::delay(125);

    chassis.moveToPoint(-32, 32, 2000,{},false);
    stickMotor.move_absolute(125, 127);

    chassis.moveToPose(-10, 36, 270, 1500,{.forwards=false},false);
    clampDown();
    stakeMotor.move_absolute(125, 75);

    chassis.moveToPoint(-46, 46, 3000,{});
    pros::delay(500);
    intake();

    pros::delay(2500);

    chassis.moveToPoint(-30, 30, 1500,{.forwards=false},false);
    clampUp();

    chassis.moveToPoint(-47,24,2500,{});
    stopIntake();


    chassis.turnToPoint(-46, 0, 1250,{.forwards=false,.maxSpeed=90},false);
    chassis.moveToPoint(-46, -13, 2500,{.forwards=false,.maxSpeed=105},false);
    clampDown();
    pros::delay(100);

    chassis.turnToPoint(-28, -5, 1750,{.forwards=false});
    chassis.moveToPoint(-28,-5,2500,{.forwards=false},false);


    chassis.turnToPoint(-56, 5, 1250);
    chassis.moveToPoint(-56, 5, 2500);
    intake();

    // chassis.moveToPoint(-58, 7,1000);

    pros::delay(1500);

    

    chassis.moveToPoint(-48, -5, 2000,{.forwards=false});
    
    chassis.turnToHeading(0, 750);
    // clampUp();
    stopIntake();
    chassis.turnToHeading(45, 750);
    chassis.moveToPoint(-24, 3, 1750,{.maxSpeed=80});

    stopIntake();

}

void redTopRush(){

    chassis.setPose(-49,32,270);

    stickMotor.move_absolute(75,70);
    chassis.moveToPoint(-11, 46, 1750,{.forwards=false,.minSpeed=80,.earlyExitRange=10},false);
    stickMotor.move(-127);
    pros::delay(125);

    chassis.moveToPoint(-32, 32, 2000,{},false);
    stickMotor.move_absolute(125, 127);

    chassis.moveToPose(-10, 36, 270, 1500,{.forwards=false},false);
    clampDown();
    stakeMotor.move_absolute(125, 75);

    chassis.moveToPoint(-48, 48, 3000,{});
    pros::delay(500);
    intake();

    pros::delay(2500);

    chassis.moveToPoint(-24, 24, 1500,{.forwards=false},false);
    clampUp();

    chassis.moveToPoint(-47,24,2500,{});
    stopIntake();


    chassis.turnToPoint(-46, 0, 1250,{.forwards=false,.maxSpeed=90},false);
    chassis.moveToPoint(-46, -13, 2500,{.forwards=false,.maxSpeed=105},false);
    clampDown();
    pros::delay(100);

    chassis.turnToPoint(-28, -5, 1750,{.forwards=false});
    chassis.moveToPoint(-28,-5,2500,{.forwards=false},false);


    chassis.turnToPoint(-56, 5, 1250);
    chassis.moveToPoint(-56, 5, 2500);
    intake();

    chassis.moveToPoint(-58, 7,1000);

    pros::delay(1500);

    

    chassis.moveToPoint(-48, -5, 2000,{.forwards=false});
    
    chassis.turnToHeading(0, 750);
    // clampUp();
    stopIntake();
    chassis.turnToHeading(45, 750);
    chassis.moveToPoint(-24, 3, 1750,{.maxSpeed=80});

    stopIntake();


}

void blueBottomRush(){


    chassis.setPose(49,-32,90);

    stickMotor.move_absolute(75,70);
    chassis.moveToPoint(11, -46, 1750,{.forwards=false,.minSpeed=80,.earlyExitRange=10},false);
    stickMotor.move(-127);
    pros::delay(125);

    chassis.moveToPoint(32, -32, 2000,{},false);
    stickMotor.move_absolute(125, 127);

    chassis.moveToPose(6, -36, 90, 1500,{.forwards=false},false);
    clampDown();
    stakeMotor.move_absolute(125, 75);

    chassis.moveToPoint(50, -50, 3000,{});
    pros::delay(500);
    intake();

    pros::delay(2500);

    // chassis.moveToPoint(24, -24, 1500,{.forwards=false},false);
    // clampUp();

    // chassis.turnToPoint(24, -24, 1250);

    chassis.turnToPoint(53, -61, 1250,{.forwards=false});

    chassis.moveToPoint(53, -61, 2000,{.forwards=false},false);
    clampUp();

    chassis.moveToPoint(47,-24,2500,{});
    stopIntake();


    chassis.turnToPoint(46, 0, 1250,{.forwards=false,.maxSpeed=90},false);
    chassis.moveToPoint(46, 13, 2500,{.forwards=false,.maxSpeed=105},false);
    clampDown();
    pros::delay(100);

    chassis.turnToPoint(28, 5, 1750,{.forwards=false});
    chassis.moveToPoint(28,5,2500,{.forwards=false},false);


    chassis.turnToPoint(56, -5, 1250);
    chassis.moveToPoint(56, -5, 2500);
    intake();

    chassis.moveToPoint(58, -7,1000);

    pros::delay(2500);

    

    chassis.moveToPoint(48, 5, 2000,{.forwards=false});
    
    chassis.turnToHeading(0, 750);
    // clampUp();
    stopIntake();
    chassis.turnToHeading(315, 750);
    chassis.moveToPoint(24, -3, 1750,{.maxSpeed=80});

    stopIntake();


}



/* skills */


void skills_pp(){
    chassis.setPose(-52,32,270);

    stickMotor.move_absolute(125, 127);

    // chassis.moveToPose(-24, 48, 225, 2500,{.forwards=false,.lead=.3,.minSpeed=60,.earlyExitRange=6},false);
    chassis.moveToPoint(-24, 48, 2500,{.forwards=false},false);
    clampDown();
    stakeMotor.move_absolute(200, 70);

    chassis.turnToHeading(70, 750);
    intake();
    chassis.follow(SkillsPath_1_txt, 12, 20000);
}

void skills(){

    chassis.setPose(-45,32,270);

    chassis.moveToPose(-24, 48, 225, 2500,{.forwards=false,.lead=.3,.minSpeed=60,.earlyExitRange=6});
    chassis.waitUntilDone();
    clampDown();
    stakeMotor.move_absolute(200, 70);

    // chassis.turnToHeading(float theta, int timeout)

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