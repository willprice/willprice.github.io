---
layout: post
title: "Arduino -> Processing serial communication"
description: ""
category: 
tags: []
---
### Preface

I've started reading "Making Things Talk", the first edition. I bought it a
while ago when I had little experience with microcontrollers and had trouble
even understanding what for loops were doing. Now I'm a little more experienced,
I'm interested in learning how protocols work -- this seemed liked the perfect
book to consult for a beginner in communications.

Reading through the first chapter was fairly dull as I already knew most things,
the conversation on debugging communications was interesting, something I'll
definitely refer to if I have issues.

In chapter 2, a project called 'Monski Pong' is introduced, this involved a
monkey with flex sensor attached to it's arms. These sensors are read by an
arduino which communicates it's data via serial to a processing sketch, which
uses it to control a game of pong. I was mostly interested in how the
communication works, and less in the game of pong, however I did rewrite the
game in an OO fashion (badly) to get some practice and make sure I don't forget
the syntax etc.

### Communication:
The processing sketch sends the arduino linefeeds which are interpreted as
requests for data, the arduino then sends the data and the sketch reads the data
in as a string, trims it of whitespace and interprets it as a number.

{% highlight java %}
/* PROCESSING CODE */
import processing.serial.*

Serial myPort;    // Declare serial port
void setup() {
   // Setup serial port as first available port, at 9600 baud
   myPort = new Serial(this, Serial.list()[0], 9600);

   // 10 in ASCII == linefeed
   myPort.bufferUntil(10);
}
   
void draw() {}

void serialEvent(Serial myPort) {
   // Read the data in the serial buffer until the linefeed
   String myString = myPort.readStringUntil(linefeed);

   // Clean up string, remove all whitespace from start and end
   myString = trim(myString);

   // If the string isn't just a linefeed, read the contents as the sensor value
   if (myString != null) {
      int sensor = int(myString);
   
   // Display the value in the console
   println(sensor);
   
   // Send a linefeed to the arduino, to request another sensor value
   myPort.write('\r');
}
{% endhighlight %}

{% highlight c %}
/* ARDUINO CODE */
int sensorVal = 0;

void setup() {
   Serial.begin(9600);
}

void loop() {
   sensorVal = analogRead(0);

   // Wait for a message
   if (Serial.available() > 0) {
      // Empty the serial buffer
      int inByte = Serial.read();
      
      // Now send response
      Serial.print(sensorVal)
   }
}
{% endhighlight %}
