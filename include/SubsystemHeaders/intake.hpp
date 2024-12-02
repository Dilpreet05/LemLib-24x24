#include "api.h"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"

extern pros::Motor flexWheelIntakeMotor;
extern pros::Motor hookIntakeMotor;
inline int intakeSpeed = 127;


void setIntakeBrakes();
void intakeControl();



extern pros::Task colorSorting;
inline pros::Optical intakeColorSensor(18);
inline bool isLoaded = false;
inline int sortColor = 0;
inline bool isStuck = false;