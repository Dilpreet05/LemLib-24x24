#include "api.h" // IWYU pragma: keep

// inline bool isRunningAuton = false;

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

void liftMove(int);
void stickMove(int n);

void skills();
void findStartingPose();
void intakeStuckTask();


void red_D();
void blue_D();
void blue_K();
void red_K();

inline bool intakeStuckTaskOn = false;
extern pros::Task intake_stuck_task;