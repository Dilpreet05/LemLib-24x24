#include "main.h"
// #include "pros/motors.hpp"


extern pros::Motor stakeMotor;
extern lemlib::PID stakePID;

void setStakeMotorBrake();
void moveStakeMech();
void tuneStakePID();