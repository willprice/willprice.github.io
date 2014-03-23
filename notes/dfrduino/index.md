---
layout: layout
---
# DFRduino Robot Workshop

Hello everyone! I hope we do have an enjoyable workshop. If you find anything
this difficult to understand, find me at the end of the session and please do
say, it'll help me make it clearer for the next run of the workshop.

## Requirements
* Some knowledge of Arduino programming (if lacking see [tutorial](intro.html)).
* A laptop with wifi and the [Arduino IDE](http://arduino.cc/en/Main/Software).
* A DFDuino robot *(provided by us at the workshop)*

If you're unsure of whether you have a sufficient level of programming skill,
see whether you can understand the code below. I've commented it to try and help
you understand it. If you have trouble, try reading my introduction and
following the Arduino links at the bottom of the page. 

{% highlight c %}
// Declare the variables we'll use in the sketch
// Definitions of variables come in the form:
// [type] [name] = [value];
// int stands for integer (a whole number, not a decimal)
int delayTimeInMiliSeconds = 500;
// LEDs are a type of light
// A pin is a port on the arduino in which we can plug wires into and control
// things
int ledPin = 13;

// setup() runs only once
void setup() {
    // Set the ledPin (13) to be an output
    pinMode(ledPin, OUTPUT);
}

// Loop runs continuously, when it's finished, it reruns itself
void loop() {
    // Here we run the 'flash()' function over and over again
    flash();
}

// This is the 'flash()' function definition
// Function definitions look like this:
// [type] [name]() {
//      [code]
// }
// 'type' is the type of value returned if you use any 'return' statments in
// your function. E.g. 'void' if you don't return anything.
// 'name' is the name you use to run the code, e.g. 'flash'
// 'code' is the code that your function will run when you call it. 'call'ing a
// function is achieved by writing 'name()'
//
// The curly braces: '{' and '}' enclose the code that runs when
// 'flash()' is run.
void flash() {
    // digitalWrite allows us to control a pin (in this case, pin 13) and change
    // it's value.
    digitalWrite(ledPin, HIGH);
    // delay for the amount of time we declared at the start of the sketch
    delay(delayTimeInMiliSeconds);
    // output a LOW (0V) signal on the ledPin
    // this turns the LED off, as it will no longer have a current flowing
    // through it
    digitalWrite(ledPin, LOW);
    // Again, delay like last time
    delay(delayTimeInMiliSeconds);
}
{% endhighlight %}

## Outline of the workshop:
1. [**PRIMER**: Introduction to Arduino and C](intro.html) **(IMPORTANT for beginners with little experience)**, if you're already familiar with programming, just
   take a brief look and then move on to the workshop material.
2. [Introduction to the DFDuino robot platform](intro-dfduino.html)
3. [Making your robot move](moving.html)
4. [Sensing distance](sensing.html)
5. [Avoiding obstacles](avoiding.html)

Also see [Debugging (fixing problems)](debugging.html)


If you were smitten with the robot and want to build one yourself then you can
find a list of components [here](parts.html)
## Helpful links
Throughout the workshop you may find you have gaps in your knowledge. You should
be able to find out everything you need to know at these links:

* [Arduino](http://www.arduino.cc/)
* [Arduino bare minimum program](http://arduino.cc/en/Tutorial/BareMinimum)
* [Arduino blink an LED](http://arduino.cc/en/Tutorial/Blink)
* [Arduino introduction](http://arduino.cc/en/Guide/Introduction) 
* [Arduino getting started](http://arduino.cc/en/Guide/HomePage)
* [Arduino programming reference](http://arduino.cc/en/Reference/HomePage)
* [DFRduino](http://www.dfrobot.com/wiki/index.php/DFRduino_Romeo-All_in_one_Controller_(SKU:DFR0004\))
* [DFRduino Library Reference](doc/classDFRduino.html)
* [DFRduino Github repository](http://github.com/willprice/DFRduino)
