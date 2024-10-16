#include "main.h" // IWYU pragma: keep


void tuneAngularPID();
void tuneAngularWindUp();
void tuneLinearPID();
void tuneLinearWindUp();


void clampUp();
void clampDown();

void intake();
void outtake();
void stopIntake();
void switchIntakeSpeed();
void intakeTask(void* parameter);
void stickUp();
void stickDown();

void liftMove();

void redRightSide();

/* 1 represents red, -1 represents blue */
void bottomRush(int color);