#include "main.h"
#include "gif-pros/gifclass.hpp"
// #include "asset.h" // IWYU pragma: keep

// This file exists just so that we can have a global variables that dont belong to a subsystem.
Gif *gif;
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Helper function to set brakes on all subsystems
void setBrakes()
{
    setIntakeBrakes();
    setStakeMotorBrake();
    setStickBrakes();
}

// Helper function to check motor temperatures and print the average
void check_motors_and_get_temps()
{
    std::vector<pros::Motor> motors = {
        pros::Motor(-2),
        pros::Motor(-3),
        pros::Motor(-4),
        pros::Motor(8),
        pros::Motor(9),
        pros::Motor(10),
        pros::Motor(20),
        pros::Motor(12),
        pros::Motor(5),
    };

    double totalTemp = 0.0;
    int count = 0;

    for (auto &motor : motors)
    {
        double temp = motor.get_temperature();
        if (temp == PROS_ERR_F)
        { // PROS_ERR_F is returned when the motor is unplugged
            pros::lcd::print(4, ("Uplugged motor on port " + std::to_string(motor.get_port())).c_str());
            pros::delay(250);
            master.rumble(".");
        }

        if (count < 6)
        {
            totalTemp += temp;
        }
        ++count;
    }

    double averageTempCelsius = totalTemp / count;
    double averageTempFahrenheit = averageTempCelsius * 9.0 / 5.0 + 32.0;
    //   print_to_screen("Avgerage Temp: " + std::to_string(averageTempFahrenheit), 4);
    pros::lcd::print(4, ("Average Temp: " + std::to_string(roundf(averageTempFahrenheit))).c_str());
}