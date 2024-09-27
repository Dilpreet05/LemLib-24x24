#include "main.h"
#include "pros/misc.h"

pros::adi::DigitalOut leftClampPiston('C',LOW);
pros::adi::DigitalOut rightClampPiston('D',LOW);

void updateClamp(){

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        leftClampPiston.set_value(1);
        rightClampPiston.set_value(1);
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
        leftClampPiston.set_value(0);
        rightClampPiston.set_value(0);
    }

}