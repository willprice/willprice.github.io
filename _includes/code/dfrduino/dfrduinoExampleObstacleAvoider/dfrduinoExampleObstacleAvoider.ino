#include <DFRduino.h>
#include <Servo.h>

DFRduino robot;

void setup() {
  Serial.begin(9600);
  resetHeadPosition();
}

void loop() {
  explore();
}

void explore(void) {
  robot.setMotors(80, 90);
  delay(100);
  if (robot.readDistanceInCentimeters() < 30) {
    //Don't move while we survey the obstacles!
    robot.setMotors(0, 0);
    int leftDistance = lookLeft();
    int rightDistance = lookRight();
    makeDecisionOnWhereToTurnNext(leftDistance, rightDistance);
  }
}

void makeDecisionOnWhereToTurnNext(int leftDistance, int rightDistance) {
  if (leftDistance > rightDistance) {
    robot.setDirection('l');
  } else {
    robot.setDirection('r');
  } 
  if (analogRead(3) % 4 == 0)
    robot.setDirection('b');
  delay(200);
}

int lookLeft(void) {
  robot.setHorizontalHeadPosition(150);
  waitForServoToReachPosition();
  int distance = robot.readDistanceInCentimeters();
  resetHeadPosition();
  return distance;
}

int lookRight(void) {
  robot.setHorizontalHeadPosition(30);
  waitForServoToReachPosition();
  int distance = robot.readDistanceInCentimeters();
  resetHeadPosition();
  return distance;
}

void resetHeadPosition(void) {
  robot.setHorizontalHeadPosition(90);
  robot.setVerticalHeadPosition(120);
  waitForServoToReachPosition();
}

void waitForServoToReachPosition(void) {
  delay(500);
}
