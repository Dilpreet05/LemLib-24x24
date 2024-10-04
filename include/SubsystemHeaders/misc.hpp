#include "api.h" // IWYU pragma: keep
#include "gif-pros/gifclass.hpp" // IWYU pragma: keep

extern Gif* gif;
extern pros::Controller master;

void setBrakes();
void check_motors_and_get_temps();
bool ring_is_red();
bool ring_is_blue();