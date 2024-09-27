#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include <cstdint>

pros::Motor stakeMotor(11,pros::MotorGearset::green,pros::MotorUnits::degrees);
pros::adi::DigitalOut leftSide('H',LOW);
pros::adi::DigitalOut rightSide('G',LOW);
int pistonState = 0;

void moveStakeMech(){

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
        stakeMotor.move(127);
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        stakeMotor.move(-127);
    }else{
        stakeMotor.brake();
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        pistonState=!pistonState;
        leftSide.set_value(pistonState);
        rightSide.set_value(pistonState);
    }

    

}

void setStakeMotorBrake(){

    stakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}