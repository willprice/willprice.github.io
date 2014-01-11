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
`DFRduino` that allows you to control the robot at a higher level. This will
allow us to design an obstacle avoiding robot in a few hours!
