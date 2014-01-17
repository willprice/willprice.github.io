#include <Servo.h>
#include <DFRduino.h>


DFRduino robot;

void setup() {
}

void loop() {
  // Providing there are no delays in our code, this loop is being run
  // thousands of times a second. Think about how that might affect the
  // code you write

  if (robot.readDistanceInCentimeters() < 30) {
    // Go back for 1 second
    robot.setDirection('b');
    delay(1000);
    // Turn right by approximately 90 degrees
    robot.setDirection('r');
    delay(350);
  } else {
    // Otherwise we'll just go forward 
    robot.setDirection('f');
    delay(100);
  }
}
