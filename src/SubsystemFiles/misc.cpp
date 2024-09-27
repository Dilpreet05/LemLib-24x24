#include "main.h"
#include "gif-pros/gifclass.hpp"
// #include "asset.h" // IWYU pragma: keep


// This file exists just so that we can have a global variables that dont belong to a subsystem.
Gif* gif; 
pros::Controller master(pros::E_CONTROLLER_MASTER);