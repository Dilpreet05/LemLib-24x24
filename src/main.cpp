#include "main.h"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rotation.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

/* Motor Groups declaration and initialization */

/**
 * 
 ** left_motors represents the grouping of motors that are on the LEFT side of the DRIVETRAIN
 
 * ARGUMENTS:
 * 
 ** The first argument in left_motors represents the ports that each motor is connected to.
 * ! in this case our motor ports will be negative, negativity in motor ports indicates that the motor should be spinning in a reversed direction.
 * ! with a positive port, motors spin clockwise at a positive input. With a negative port, motors spoin counterclockwise at a positive input.
 * 
 ** The second argument represents the gearset of the motor
 * ! There are different types of gearsets: Red, Green, and Blue.
 * ! Blue being the fastest at 600PM, Red being the slowest at 100RPM, and Green being the middle range at 200RPM.
 * 
 */
/* Arguments:

 * The first argument in left_motors represents the ports that each motor is connected to
 * 	- in this case our motor ports will be negative, negativity in motor ports indicates that the motor should be spinning in a reversed direction
 *	- with a positive port, motors spin clockwise at a positive input. with a negative port, motors spin counterclockwise at a positive input.

 * The second argument represents the gearset of the motor.
 *	- There are different types of gearsets: Red, Green, Blue, with 
 *	- blue being the fastest at 600RPM, Red being the slowest at 100RPM, and Green being the middle range at 200RPM

 */
pros::MotorGroup left_motors({-1, -2, -3}, pros::MotorGearset::blue); // Motor ports {1,2,3} at 600RPM (Blue gearset)



/**
 ** Same logic from left_motors applies to right_motors, including arguments and motor gearsets.
 ** Right_motors represents the grouping of motors that are on the RIGHT side of the DRIVETRAIN
 ** Positive motor ports because the motors should be spinning clockwise for the robot to move forward.
 */
pros::MotorGroup right_motors({4, 5, 6}, pros::MotorGearset::blue); // Motor ports {4,5,6} at 600RPM

/* End of Motor Group declaration and initialization */


/* Start of DRIVETRAIN code */

/**
 * ! This block of code creates a DRIVETRAIN object,
 * 
 *  
 ** This stores our left side motors, right side motors, our TRACKWIDTH, WHEELDIAMETER, 
 ** DRIVERPM, and our HORIZONTALDRIFT value 
 *
 * TRACKWIDTH:
 * ! The distance between the left side and right side of the DRIVETRAIN.
 * ! Specifically from the middle of the wheels.
 * 
 * WHEELDIAMETER:
 * ! The diameter of our DRIVETRAIN wheels. We measured using calipers.
 * 
 * DRIVERPM:
 * ! The speed our wheels will spin at, this value is different from the motor RPM because we are using a gear ratio,
 * ! Our DRIVETRAIN gearing consists of a 36T gear input and a 48T gear output,  this comes out to be a 3/4 ratio or 0.75,
 * ! We take this 0.75 value and multiply it by our motor RPM to find our DRIVETRAIN wheel RPM,
 * ! Our robot uses a 600RPM motor with a 0.75 gear ratio, making our DRIVETRAIN RPM become 450RPM.
 * 
 * HORIZONTALDRIFT:
 * ! A feature that ensures compatibility with multiple types of DRIVETRAINS,
 * ! with both all omni wheels (drift drive), or DRIVETRAINS with center traction wheels.
 * ! It controls how fast the chassis can move while turning, a higher value means,
 * ! The robot has less physical ddrift when driving and turning in auton and lower value means the opposite.
 * ! We use our default value of 8 because we have center traction wheels which allow us to grip the field more proper.
 * b
 * 
 */


lemlib::Drivetrain DRIVETRAIN(&left_motors, // left motor group
                              &right_motors, // right motor group
                              11.5, // Track width: 11.5 INCHES
                              2.75, // Wheel diameter of our 3D Printed custom Omni Wheels & VEX Traction wheels
                              450, // drivetrain rpm: 450 RPM
                              8 // horizontal drift: 8 
);


/*  End of Drive Train Code */


/* Start of Odomoetry Code */

/**
 * 
 *?s What is odometry?
 ** Odometry is the use of data from motion sensors to estimate change in position over time,
 ** It is used in robotics by some legged or wheeled robots to estimate their position relative to a starting location.
 ** In our case, we will be using traacking wheels in order to track our robots position accurately and percisely.
 * 
 *? Why use odometry?
 ** We use odometry for consistincy of autonomous rutines including both skills autonomous and match autonomous.
 * 
 */


/**
 * 
 *? For our odometry, we use readings from 2 unique sensors and 3 total sensors:
 **  1. An IMU (Inertial Measurement Unit) using a Vex V5 Inertial Sensor
 **  2. Vertical Tracking wheel using a Vex V5 Rotation Sensor
 **  3. Horizonal Tracking wheel using a Vex V5 Rotation Sensor.
 * 
 * IMU:
 * 	! this is used in order to find our current heading value which is the current direction the robot is facing.
 * 	! we can use this value in our odometry to make sure that our robot faces the proper direction when commanded to.
 * 
 * 
 */
pros::Imu IMU(10);



/**
 * 
 * HORIZONTALTRACKINGSENSOR:
 * ! tracks any movement in the horizontal direction of our robot, this is use a lot in the case where our auton paths stray
 * ! due to horizontal contact from our or opposing alliance robots.
 * 
 * VERICALTRACKINGSENSOR:
 * ! tracks vertical movement/straight movements of the robot. 
 * ! This allows us to accurately move our robot a specific amount of units forward, as well as account for any contact.
 * 
 * 
 */
pros::Rotation horizontalTrackingWheelSensor(12);
pros::Rotation verticalTrackingWheelSensor(13);



lemlib::TrackingWheel horizontalTrackingWheel(&horizontalTrackingWheelSensor,2.76,0);
lemlib::TrackingWheel verticalTrackingWheel(&verticalTrackingWheelSensor,2.76,0);



lemlib::OdomSensors sensors(&verticalTrackingWheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontalTrackingWheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &IMU // inertial sensor
);

/* End of Odometry Code*/

/* Start of PID Code */

// lateral PID controller
lemlib::ControllerSettings lateralController (10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angularController (2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


/* End of PID Code */

/* Start of chassis */

lemlib::Chassis chassis(DRIVETRAIN, // drivetrain settings
						lateralController, // lateral PID settings
						angularController, // angular PID settings
						sensors // odometry sensors
);


/* End of Chassis */



/* Start of Intake Code */

// placeholder motor ports.
pros::Motor flexWheelIntakeMotor(10,pros::MotorGearset::green,pros::v5::MotorUnits::degrees);
pros::Motor hookIntakeMotor(11,pros::MotorGearset::green,pros::v5::MotorUnits::degrees);



void spinIntake(){

	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
		flexWheelIntakeMotor.move(127);
	}else{
		flexWheelIntakeMotor.move(0);
		flexWheelIntakeMotor.brake();
	}

	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
		hookIntakeMotor.move(127);
	}else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
		hookIntakeMotor.move(-127);
	}else{
		hookIntakeMotor.move(0);
		hookIntakeMotor.brake();
	}
	


}

void setIntakeBrakes(){

	flexWheelIntakeMotor.set_brake_mode(pros::MotorBrake::coast);
	hookIntakeMotor.set_brake_mode(pros::MotorBrake::coast);

}



/* End of Intake Code */




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


// void initialize() {
// 	pros::lcd::initialize();
// 	pros::lcd::set_text(1, "Hello PROS User!");
// 	setIntakeBrakes();
// }

void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1, -2, 3});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4, 5, -6});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6


	while (true) {

		spinIntake();

	}
}