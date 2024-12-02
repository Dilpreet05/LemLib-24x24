#include "main.h"

/* Start of Intake Code */

// Placeholder motor ports.
pros::Motor flexWheelIntakeMotor(20, pros::MotorGearset::green, pros::v5::MotorUnits::degrees);
pros::Motor hookIntakeMotor(12, pros::MotorGearset::red, pros::v5::MotorUnits::degrees);


void intakeControl()
{
    // Outtake while holding R2
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        hookIntakeMotor.move(intakeSpeed);
        flexWheelIntakeMotor.move(intakeSpeed);
    }

    // Intake while holding R1
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) )
    {
        hookIntakeMotor.move(-intakeSpeed);
        flexWheelIntakeMotor.move(-intakeSpeed);
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


pros::Task colorSorting{[]{

    intakeColorSensor.set_led_pwm(100);



    
    while(true){


        /* when the specified color */
        if(sortColor==1){

            isLoaded = (intakeColorSensor.get_hue()>5 && intakeColorSensor.get_hue()<30) ? true:false; /* if the ring is red, prepare to get rid of it */

        }else if(sortColor==-1){

            isLoaded = (intakeColorSensor.get_hue()>185 && intakeColorSensor.get_hue()<215) ? true:false; /*  if the ring is blue, prepare to get rid of it */

        }


        /* if the motors current draw is massive, it's probably stuck */
        if(hookIntakeMotor.get_current_draw()>2300){
            isStuck = true;
        }



        if((isLoaded && hookIntakeMotor.get_actual_velocity()>50) || (isStuck) ){

            /* reverse intake for specified time. if intake is stuck then reverse for longer */
            hookIntakeMotor.move(intakeSpeed);
            pros::delay(125 + 125*(isStuck*2));
            hookIntakeMotor.move(-intakeSpeed);


            /* reset */
            isStuck = false;
            isLoaded=false;
        }

        pros::delay(20);

    }


    
}};