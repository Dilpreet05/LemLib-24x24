#include "api.h" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"

extern lemlib::Chassis chassis;
extern lemlib::ControllerSettings angularController;
extern lemlib::ControllerSettings lateralController;
extern lemlib::OdomSensors sensors;
extern lemlib::TrackingWheel horizontalTrackingWheel;
extern lemlib::TrackingWheel verticalTrackingWheel;
extern pros::Rotation horizontalTrackingWheelSensor;
extern pros::Rotation verticalTrackingWheelSensor;
extern pros::Imu IMU;
extern lemlib::Drivetrain DRIVETRAIN;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

void chassisControl();