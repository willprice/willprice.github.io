#include <Servo.h>
#include <DFRduino.h>


DFRduino robot;

void setup() {
}

void loop() {
  // Look forward
  // Unfortunately my robot's vertical servo is not calibrated very
  // well, so looking ahead is 130 degrees, less points it up, more
  // makes it click a lot -- if your's clicks a lot, pull out the cable,
  // and rewrite your code so that it won't put it to such extreme a
  // position
  robot.setVerticalHeadPosition(130);
  // Wait for the servo to move
  delay(500);
  // Look upwards
  robot.setVerticalHeadPosition(40);
  // Wait for the servo to move
  delay(500);
}
