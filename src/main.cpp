#include "main.h"


/* Motor Groups declaration and initialization */

// left_motors represents the grouping of motors that are on the LEFT side of the drive-train
/* Arguments:

 * The first argument in left_motors represents the ports that each motor is connected to
 * 	- in this case our motor ports will be negative, negativity in motor ports indicates that the motor should be spinning in a reversed direction
 *	- with a positive port, motors spin clockwise at a positive input. with a negative port, motors spin counterclockwise at a positive input.

 * The second argument represents the gearset of the motor.
 *	- There are different types of gearsets: Red, Green, Blue, with 
 *	- blue being the fastest at 600RPM, Red being the slowest at 100RPM, and Green being the middle range at 200RPM

 */
pros::MotorGroup left_motors({-1, -2, -3}, pros::MotorGearset::blue); // Motor ports {1,2,3} at 600RPM (Blue gearset)

// same logic from left_motors applies to right_motors, including arguments and motor gearsets.
// right_motors represents the grouping of motors that are on the RIGHT side of the drive-train
// positive motor ports because the motors should be spinning clockwise for the robot to move forward.
pros::MotorGroup right_motors({4, 5, 6}, pros::MotorGearset::blue); // Motor ports {4,5,6} at 600RPM

/* End of Motor Group declaration and initialization */


/* Start of Drive Train code */

/**
 * This block of code creates a drivetrain object,
 * 
 * This stores our left side motors, right side motors, our track width, wheel diameter, Drive RPM, and our horizontal drift value
 *
 * Track Width - the distance between the left side and right sides of the drivetrain. 
 *				 Specifically, from the middle of the wheels.
 *
 * Wheel diameter - The diameter of our drive train wheels. We measured using calipers.
 *
 * Drive RPM - The speed our wheels will spin at, this value is different from the Motor RPM because we're using a gear ratio,
 *			   Our drive train gearings consists of a 36t Gear input and a 48t output, this comes out to be a 3/4 ratio or 0.75,
 *			   We take this 0.75 value and multiply it by our motor RPM to find our drivetrain/wheel RPM,
 *			   Our robot uses a 600RPM motor with a 0.75 gear ratio, making our drivetrain RPM become 450RPM.
 *
 * Horizontal Drift -  A feature that ensures compatibility with mutliple types of drivetrains , 
 *					   with both all omni wheels (drift drive), or drivetrains with center traction wheels.
 *					   It controls how fast the chassis can move while turning, a higher value means 
 *					   The robot has less physical drift when driving and turning in auton and lower value means the opposite.
 *					   We use our default value of 8 because we have center traction wheels which allows us to grip the field better.
 *
 */

lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              11.5, // Track width: 11.5 INCHES
                              2.75, // Wheel diameter of our 3D Printed custom Omni Wheels & VEX Traction wheels
                              450, // drivetrain rpm: 450 RPM
                              8 // horizontal drift: 8 
);


/*  End of Drive Train Code*/







/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
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
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		// Arcade control scheme
		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		left_mg.move(dir - turn);                      // Sets left motor voltage
		right_mg.move(dir + turn);                     // Sets right motor voltage
		pros::delay(20);                               // Run for 20 ms then update
	}
}