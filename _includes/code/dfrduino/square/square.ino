#include <Servo.h>
#include <DFRduino.h>


DFRduino robot;
// How long shall we move forward for? (in milliseconds)
int delayTime = 1000;
// This depends on how charged your batteries are. This works for me on 
// new batteries
int timeTakenToMoveNinetyDegrees = 350;

void setup() {
}

void loop() {
  // Move forward
  robot.setDirection('f');
  delay(delayTime);
  // Turn right
  robot.setDirection('r');
  // wait until we've rotated 90 degrees
  delay(timeTakenToMoveNinetyDegrees);
  // When we loop again, we'll go forward
}
