#include "main.h"
// #include "pros/misc.h"

pros::adi::DigitalOut leftClampPiston('A', LOW);
pros::adi::DigitalOut rightClampPiston('B', LOW);

void updateClamp()
{
    // Press L1 to clamp down
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
    {
        leftClampPiston.set_value(1);
        rightClampPiston.set_value(1);
    }

    // Press L2 to clamp up
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
    {
        leftClampPiston.set_value(0);
        rightClampPiston.set_value(0);
    }
}