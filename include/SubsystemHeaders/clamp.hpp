#include "main.h"

extern pros::adi::DigitalOut leftClampPiston;
extern pros::adi::DigitalOut rightClampPiston;
inline bool isClampDown = false;

void updateClamp();
