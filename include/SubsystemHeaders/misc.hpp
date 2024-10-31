#include "api.h" // IWYU pragma: keep
#include "robodash/api.h" // IWYU pragma: keep

extern pros::Controller master;
extern rd::Selector selector;
extern rd::Console console;

void setBrakes();
void check_motors_and_get_temps();
bool ring_is_red();
bool ring_is_blue();