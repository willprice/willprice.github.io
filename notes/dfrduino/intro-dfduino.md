---
layout: layout
---

The DFRduino is an Arduino based robot. It's programmed through the Arduino
IDE program. You'll be using a library I wrote that saves you from having to
write code like this:
{% highlight c %}

void setup() {
    pinMode(LEFT_MOTOR_DIRECTION_CONTROL, OUTPUT);
    pinMode(LEFT_MOTOR_SPEED_CONTROL, OUTPUT);
    pinMode(RIGHT_MOTOR_DIRECTION_CONTROL, OUTPUT);
    pinMode(RIGHT_MOTOR_SPEED_CONTROL, OUTPUT);
}

void loop() {
    goForward();
} 

void goForward() {
    digitalWrite(LEFT_MOTOR_DIRECTION_CONTROL, HIGH);
    analogWrite(LEFT_MOTOR_SPEED_CONTROL, 100);
    digitalWrite(RIGHT_MOTOR_DIRECTION_CONTROL, LOW);
    analogWrite(RIGHT_MOTOR_SPEED_CONTROL, 100);
}
{% endhighlight %}

This is rather slow way to develop code, so I've encapsulated (hidden the low
level details) the robot dependent things and given you a library called
`DFRduino` that allows you to control the robot at a higher level through the
use of some functions. This will allow us to design an obstacle avoiding robot
in a few hours without getting stuck trying to figure out how to get the robot
to go forward! *(although, if people are interested in approaching robots at a
lower level of detail talk to me at the end of the workshop and I'll see if i
can arrange one for next DigiMakers)*.

Instead of the above code, you'll be writing something like:

{% highlight c %}
// Import the DFRduino library and Servo library
#include <DFRduino.h>
#include <servo.h>

DFRduino robot;

void setup() {

}

void loop() {
    // Make the robot go forward
    robot.setDirection('f');
}
{% endhighlight %}

## Features of the DFRduino robot
* 2 wheel drive.
* Sharp IR distance measuring sensors (range: 20cm -- 150cm) mounted on twin
  servo head.

## Library functions
The library I have written contains a set of functions to help you develop your
obstacle avoiding robot.

### Types of parameters
* `[percentage]` can be -100 to 100.
* `[angle]` can be 0 to 180.
* `[char]` can be any character inside of single quotes, e.g. `'f'`.

### Functions
* `void setDirection([char])`:
  * `'f'` - forward.
  * `'b'` - backward.
  * `'l'` - spin left (spins on the spot).
  * `'r'` - spin right (spins on the spot).

| `[return type]` | `[name]` | `[parameters]` | Explanation | 
|-----------------|----------|----------------|-------------|
| `void`          | `setMotors` |  `([left percentage], [right percentage])` |  Set the motor speed by percentage of maximum speed, e.g. `setMotors(100, 100)` is full thrust forward. |
| `void`          | `setVerticalHeadPosition` | `([angle])` | Sets the vertical angle of the IR sensor (we call this the head). For me looking straight ahead was 130, you'll have to play around with this to figure out which values do what. |
| `void`          | `setHorizontalHeadPosition` | `([angle])` | Sets the horizontal angle of the head. 0 for left, 90 for forward, 180 for right. |
| `int` | `readDistanceInCentimeters` | NONE  | Reads the distance from the IR sensor and returns the distance in centimeters. |
