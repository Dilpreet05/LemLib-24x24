#include "main.h"
// #include "pros/motors.hpp"


extern pros::Motor stakeMotor;
extern pros::adi::DigitalOut leftSide;
extern pros::adi::DigitalOut rightSide;

void setStakeMotorBrake();
void moveStakeMech();