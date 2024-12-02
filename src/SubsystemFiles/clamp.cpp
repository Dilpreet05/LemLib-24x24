#include "main.h"
// #include "pros/misc.h"

pros::adi::DigitalOut leftClampPiston('D', LOW);
pros::adi::DigitalOut rightClampPiston('C', LOW);

void updateClamp()
{   
    if (master.get_digital_new_press(DIGITAL_DOWN))
    {
        leftClampPiston.set_value(isClampDown ? 0 : 1);
        rightClampPiston.set_value(isClampDown ? 0 : 1);
        isClampDown = !isClampDown;
    }
}