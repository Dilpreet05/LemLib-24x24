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

void clampDown()
{
    leftClampPiston.set_value(1);
    rightClampPiston.set_value(1);
    isClampDown=1;
}

void clampUp()
{
    leftClampPiston.set_value(0);
    rightClampPiston.set_value(0);
    isClampDown=0;
}
int desiredHookIntakeSpeed = 0;
void intake()
{
    hookIntakeMotor.move(-intakeSpeed);
    flexWheelIntakeMotor.move(-intakeSpeed);
}

void outtake()
{
    hookIntakeMotor.move(intakeSpeed);
    flexWheelIntakeMotor.move(intakeSpeed);
}

void stopIntake()
{
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

void red_K(){ // red K

    /** Set our robots position to the starting point on the field */
    chassis.setPose(-43,32,270);


    /** Move our MOGO rush stick upwards slighly to 75deg @ 70RPM => Rush towards the MOGO using the shortest path */
    stickMotor.move_absolute(75,70);
    chassis.moveToPoint(-11, 46, 1750,{.forwards=false,.minSpeed=80,.earlyExitRange=10},false);

    /** Once we reach proper position, slam the MOGO rush stick back down at max speed. */
    stickMotor.move(-127);
    pros::delay(125); // lets the MOGO become steady before next step.

    /** Drive backwards to take the MOGO away from the centerline & put it onto our side */
    chassis.moveToPoint(-32, 32, 2000,{},false);
    stickMotor.move_absolute(125, 127); // put stick back up after finished getting the MOGO.

    /** A curving motion used to align the robot to the flat edge of the MOGO,  and then drive into it with out clamp. */
    chassis.moveToPose(-8, 36, 270, 1500,{.forwards=false},false);
    clampDown(); // clamp onto MOGO
    stakeMotor.move_absolute(125, 75); // move our high stake mech out of the way

    /** Grabs the ring @ position (-48,48) */
    chassis.moveToPoint(-46, 46, 3000,{});
    pros::delay(500);
    intake(); // wait a little bit before spinning the intake.

    pros::delay(2500); // wait at (-46,46) to ensure the ring gets put into the intake -> onto the MOGO

    /** drive to the MOGO drop off point, near the ladder */
    chassis.moveToPoint(-30, 30, 1500,{.forwards=false},false);
    clampUp(); // release MOGO

    /** Drive to (-47,24) aligns us to ourside MOGO located at (-48,0) */
    chassis.moveToPoint(-47,24,2500,{});
    stopIntake(); // stop intake to prevent overuse when not necessary

    /** Grabs the MOGO at (-48,0) */
    chassis.turnToPoint(-46, 0, 1250,{.forwards=false,.maxSpeed=90},false);
    chassis.moveToPoint(-46, -13, 2500,{.forwards=false,.maxSpeed=105},false); // traveling far helps align the MOGO
    clampDown();
    pros::delay(100); // wait for the MOGO to settle in the clamp

    /** Drive to a point under the ladder, this is so we can better align for the next step */
    chassis.turnToPoint(-28, -5, 1750,{.forwards=false});
    chassis.moveToPoint(-28,-5,2500,{.forwards=false},false);

    /** Intake the ring located at (-60,0) */
    chassis.turnToPoint(-56, 5, 1250);
    chassis.moveToPoint(-56, 5, 2500);
    intake();


    pros::delay(2500); // wait until the ring is in the intake

    
    /** back up slightly & align to the ladder*/
    chassis.moveToPoint(-48, -5, 2000,{.forwards=false});
    chassis.turnToHeading(0, 750);


    /** drive to the ladder for the AWP Ladder touch */
    chassis.turnToHeading(45, 750);
    chassis.moveToPoint(-24, 3, 1750,{.maxSpeed=80},false);

    pros::delay(2500);
    stopIntake();
}

void red_D(){

    chassis.setPose(-49,32,270);

    stickMotor.move_absolute(75,70);
    chassis.moveToPoint(-11, 46, 1750,{.forwards=false,.minSpeed=80,.earlyExitRange=10},false);
    stickMotor.move(-127);
    pros::delay(125);

    chassis.moveToPoint(-32, 32, 2000,{},false);
    stickMotor.move_absolute(125, 127);

    chassis.moveToPose(-8, 36, 270, 1500,{.forwards=false,.lead=.7},false);
    clampDown();
    stakeMotor.move_absolute(125, 75);

    chassis.moveToPoint(-48, 48, 3000,{});
    pros::delay(500);
    intake();

    pros::delay(2500);

    chassis.moveToPoint(-40, 40, 1500,{.forwards=false},false);
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

void blue_K(){ // blue K

    /** Set our robots position to the starting point on the field */
    chassis.setPose(-43,32,270);

    /** Move our MOGO rush stick upwards slighly to 75deg @ 70RPM => Rush towards the MOGO using the shortest path */
    stickMotor.move_absolute(75,70);
    chassis.moveToPoint(-11, 46, 1750,{.forwards=false,.minSpeed=80,.earlyExitRange=10},false);

    /** Once we reach proper position, slam the MOGO rush stick back down at max speed. */
    stickMotor.move(-127);
    pros::delay(125);

    /** Drive backwards to take the MOGO away from the centerline & put it onto our side */
    chassis.moveToPoint(-32, 32, 2000,{},false);
    stickMotor.move_absolute(125, 127);

    /** A curving motion used to align the robot to the flat edge of the MOGO,  and then drive into it with out clamp. */
    chassis.moveToPose(-5, 36, 270, 1500,{.forwards=false},false);
    clampDown(); // latch MOGO
    stakeMotor.move_absolute(125, 75); // expand wall stake mech.

    /** Grabs the ring @ position (-48,48) */
    chassis.moveToPoint(-46, 46, 3000,{});
    pros::delay(500);
    intake();

    pros::delay(2500); // wait for ring to intake

    /** drive to the MOGO drop off point, into the positive corner */
    chassis.moveToPoint(-50, 58, 1500,{.forwards=false},false);
    clampUp(); // release MOGO
    chassis.moveToPoint(-62.321, 58.453, 1500,{.forwards=false},false); // push MOGO into corner

    /** Drive to (-47,24) aligns us to ourside MOGO located at (-48,0) */
    chassis.moveToPoint(-47,24,2500,{});
    stopIntake(); // prevent intake overuse

    /** Grabs the MOGO at (-48,0) */
    chassis.turnToPoint(-46, 0, 1250,{.forwards=false,.maxSpeed=90},false);
    chassis.moveToPoint(-46, -13, 2500,{.forwards=false,.maxSpeed=105},false);
    clampDown();
    pros::delay(100);

    /** Drive to a point under the ladder, this is so we can better align for the next step */
    chassis.turnToPoint(-28, -5, 1750,{.forwards=false});
    chassis.moveToPoint(-28,-5,2500,{.forwards=false},false);

    /** Intake the ring located at (-60,0) */
    chassis.turnToPoint(-56, 5, 1250);
    chassis.moveToPoint(-56, 5, 2500);
    intake();

    pros::delay(1500); // wait for ring to intake

    
    /** back up slightly & align to the ladder*/
    chassis.moveToPoint(-48, -5, 2000,{.forwards=false});
    chassis.turnToHeading(0, 750);

    /** drive to the ladder for the AWP Ladder touch */
    chassis.turnToHeading(45, 750);
    chassis.moveToPoint(-24, 3, 1750,{.maxSpeed=80},false);

    pros::delay(1000);
    stopIntake(); // prevent intake overuse when we finish auton before 30s

} // end of auton

void blue_D(){


    chassis.setPose(49,-32,90);

    stickMotor.move_absolute(75,70);
    chassis.moveToPoint(11, -46, 1750,{.forwards=false,.minSpeed=80,.earlyExitRange=10},false);
    stickMotor.move(-127);
    pros::delay(125);

    chassis.moveToPoint(32, -32, 2000,{},false);
    stickMotor.move_absolute(125, 127);

    chassis.moveToPose(6, -36, 90, 1500,{.forwards=false,.lead=.7},false);
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



void skills(){

    // Set global positoin for our odometry
    chassis.setPose(-52,32,270);

    /** Move to a position that allows us to clamp the MOGO at a better angle while also not affecting ring positionings */
    chassis.moveToPoint(-40, 32, 1500,{.forwards=false,.maxSpeed=60});
    stickMotor.move_absolute(125, 70);

    /** Drive towards the MOGO & Clamp onto it */
    chassis.turnToPoint(-24, 48, 750,{.forwards=false});
    chassis.moveToPoint(-24, 48, 1750,{.forwards=false},false);
    stakeMotor.move_absolute(200, 70); // This moves our wall stake mechanism out of the way. This lets us intake rings ont the MOGO.


    clampDown(); // Clamp the MOGO.
    pros::delay(250); // Let the MOGO settle into clamp before motion. Without the delay the MOGO will fling out sometimes.

    /** Driving towards our first ring at position (0,48) */
    chassis.turnToPoint(0, 48, 750);
    chassis.moveToPoint(0, 48, 1750);
    intake(); // Intake rings
    pros::delay(1750); // Delay once we reach the point where the ring is at, 
                                    // allows us to consistantly intake rings even if our flex wheels are dirty

    /** back up from the rings */
    chassis.moveToPoint(-18, 48, 1000,{.forwards=false});

    /** Drive into the ring stack at (0,60), The reason we reversed in the previous step is to avoid disturbing the state of the ring stack. */
    chassis.turnToPoint(0, 58, 750);
    chassis.moveToPoint(0, 58, 1250);
    pros::delay(1750); // delay to intake ring

    /** Reverse once again for alignment */
    chassis.moveToPoint(-18, 48, 1250,{.forwards=false});

    /** Intake the single red ring at (-24,24) */
    chassis.turnToPoint(-24,-24,750);
    chassis.moveToPoint(-24, 24, 1750,{.maxSpeed=60});
    pros::delay(1750); // delay to intake ring

    /** Intake ring at position (-48,48) */
    chassis.turnToPoint(-48, 48, 750);
    chassis.moveToPoint(-48, 48, 1750);
    pros::delay(750); // shorter delay that normal since our next motion will drive into the ring more

    /** Intake the corner ring */
    chassis.moveToPoint(-55, 55, 1750);
    pros::delay(1750); // delay to intake ring

    /** Reverse in order to spin without hitting the walls */
    chassis.moveToPoint(-48, 48, 1250,{.forwards=false});

    /** reverse into the corner and drop off the MOGO */
    chassis.turnToPoint(-58, 58, 750,{.forwards=false});
    chassis.moveToPoint(-58, 58, 1750,{.forwards=false},false);

    clampUp(); // let go of MOGO
    pros::delay(250); // delay to settle
    stopIntake(); // prevent the intake from overuse

    /** Move away from the corner and towards the center of the field */
    chassis.moveToPoint(-48, 48, 1750);
    chassis.turnToPoint(0, 48, 750,{.forwards=false});
    chassis.moveToPoint(0, 48, 3000,{.forwards=false,.maxSpeed=50},false);

    /** Drive into the second MOGO on the opposite side of the field and posses it */
    chassis.turnToPoint(24, 24, 750,{.forwards=false});
    chassis.moveToPoint(22, 26, 1750,{.forwards=false},false);
    clampDown();
    pros::delay(250); // let MOGO settle

    /** Turn to the first ring at (24,48) and intake */
    chassis.turnToPoint(18, 50, 750);
    chassis.moveToPoint(18, 50, 1750,{.maxSpeed=70});
    intake();
    pros::delay(1750); // delay to intake ring

    /** Intake ring at position (48,24) */
    chassis.turnToPoint(42, 26, 750);
    chassis.moveToPoint(42, 26, 1750,{.maxSpeed=70});
    pros::delay(1750); // delay for intake ring

    /** Intake ring at (48,48) */
    chassis.turnToPoint(42, 46, 750);
    chassis.moveToPoint(42, 46, 1750,{.maxSpeed=70});
    pros::delay(2500); // larger delay since this ring is inconsistant sometimes

    /** reverse into the corner and drop off the MOGO */
    chassis.turnToPoint(54, 62, 750,{.forwards=false});
    chassis.moveToPoint(54, 62, 1750,{.forwards=false,.minSpeed=50});
    clampUp();
    pros::delay(500);
    stopIntake();

    /** reverse and ram the MOGO to ensure its in the corner*/
    chassis.moveToPoint(59, 57, 1750,{.forwards=false,.minSpeed=50});
    chassis.moveToPoint(54, 62, 1750,{.forwards=false,.minSpeed=50});

    /** Move away from any MOGOs or rings */
    chassis.moveToPoint(48, 48, 1750); 
} // End skills