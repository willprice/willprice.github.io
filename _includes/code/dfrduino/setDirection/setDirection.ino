#include <Servo.h>
#include <DFRduino.h>


DFRduino robot;

void setup() {
}

void loop() {
  // Set the robot's direction forward
  mySetDirection('f');
}

void mySetDirection(char direction) {
  switch(direction) {
    case 'f':
      // Compensate for drifting left by reducing
      // the power of the right motor.
      robot.setMotors(100, 90);
      // If you don't break out of your switch statements,
      //  all the other cases will also be run.
      break;
    case 'b':
      robot.setMotors(-100, -90);
      break;
    case 'r':
      robot.setMotors(100, 0);
      break;
    case 'l':
      robot.setMotors(0, 100);
      break;
    default:
      // Provide some way of checking for errors in your 
      // calling code. This will be called if you don't call your
      // function with 'f', 'b', 'r' or 'l'.
      Serial.println("Direction not recognised");
      break;
  }
}
