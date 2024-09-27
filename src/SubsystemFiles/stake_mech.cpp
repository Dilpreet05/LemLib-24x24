#include "main.h"
#include "pros/misc.h"

pros::Motor stakeMotor(15,pros::MotorGearset::green,pros::MotorUnits::degrees);

void moveStakeMech(){

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
        stakeMotor.move(127);
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        stakeMotor.move(-127);
    }else{
        stakeMotor.brake();
    }

}

void setStakeMotorBrake(){

    stakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}