#include <Servo.h>
#include <DFRduino.h>


DFRduino robot;
int xIncrement = 1;
int yIncrement = 1;

int x = 0;
int y = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // '||' means OR
  if (x > 180 || x < 0) {
    xIncrement *= -1;
  }

  // The furthest down y can go is 160 degrees. If it tries to go more
  // than that the library will print out an error in the serial monitor
  if (y > 160 || y < 0) {
    // 
    yIncrement *= -1;
  }

  x += xIncrement;
  y += yIncrement;

  robot.setHorizontalHeadPosition(x);
  robot.setVerticalHeadPosition(y);
  delay(20);
}

