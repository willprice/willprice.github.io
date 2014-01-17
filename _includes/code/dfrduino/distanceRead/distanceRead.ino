#include <Servo.h>
#include <DFRduino.h>


DFRduino robot;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Print the distance sensed by the IR sensor
  Serial.print("Distance: ");
  Serial.print(robot.readDistanceInCentimeters());
  Serial.println("cm");
  delay(500);
}
