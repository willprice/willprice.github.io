---
title: "Learning Processing: Arrays"
layout: layout
tags: ['processing']
---
## ARRAYS
Array's are declared using the syntax:

{% highlight java %}
type [] name = new type [size]
{% endhighlight %}
Where _type_ is a data type, like _int_ or _float_ and _name_ is the name of the array. Finally, the _size_ is the number of elements in the array.

An example:
{% highlight java %}
// Array of 10 integers to enter ages into.
int [] ages = new int [10]
{% endhighlight %}

Initially after defining an array, it will be empty, the elements have no defined values. To set up an array, it's usually best to fill it with something, lets say 0s.
{% highlight java %}
for (int i = 0; i < ages.length; i++) {
  age[i] = 0;
}
{% endhighlight %}

## OBJECTS
Objects essentially pack up a set of variables and functions into a data structure that allows you to organise your code efficiently.

Objects are defined in a few distinct parts. Looking at an object from a top-down perspective:

- Class
  - Variables of object
  - Object constructor 
  - Functions

A _class_ is simply a way to define an object, or perhaps more intuitively a set of objects (think of yourself as a particular human, in this case, you're the object and the class is '_humans_). From the class, objects can be produced using the _constructor_ which defines which variables should be set externally through parameters (for example position etc). Variables just keep track of the data in the object. Functions take care of functionality...

{% highlight java %}
class Name {

  //data
  float var1;
  float var2;

  Name(temp_parameters) {
    var1 = var1_;
    var2 = var2_;
    // var2_ is the parameter which is then set as var2.
  }
}
{% endhighlight %}

The nice thing with objects is that you can create a whole host of _instances_ (objects that have been defined) using arrays.

{% highlight java %}
// Define the objects
object[] objects = new object[num_of_objects];

for (int i = 0; i < objects.length; i++) {
  // Initilize the objects
  objects[i] = new object(parameters);
}

while (true) {
  // Loop and perform a function on all the objects
  for (int i = 0; i < objects.length; i++) {
    objects[i].function();
  }
}

{% endhighlight %}

## TRANSFORMATIONS

Transformations are carried out by moving the origin using the `translate()` function, `translate(x,y)` moves the origin by `x` to the right and `y` down. Rotate is used to spin the canvas around the origin clockwise: `rotate(x)` will rotate the canvas by `x` radians. To handle multiple translations when dealing with lots of shapes etc, it makes sense to save transformations, this is handled by storing translations and rotations in a matrix, this matrix can be pushed to a stack using `matrixPush()` and popped using `matrixPop()` (pushing is like saving and removing, popping is like restoring, look up how stacks work).

Here's a good example of a variety of transformative functions:
{% highlight java %}
int number_of_boxes = 30;
float width_of_box = 20;
float theta;

void setup() {
  size(400, 400);
}

void draw() {
  if (numberOfBoxes < 1) {
      numberOfBoxes = 1;
  }
  background(255);

  float circumference = numberOfBoxes * widthOfBox;
  float radius = circumference/(2 * PI);
  float step = (2 * PI)/numberOfBoxes;
  // everything is drawn from the center
  translate(width/2,height/2);
  
  noFill();
  
  ellipse(0,0, radius * 2, radius * 2);
  
  fill(170,40);
  
  for (float x = 0; x < (2 * PI); x += step) {
    pushMatrix();
    rotate(x);
    translate(0, radius);
    rectMode(CENTER);
    rect(0,0,widthOfBox,widthOfBox);
    popMatrix();
  }
}

void mousePressed() {
  if (mouseX < width/2) {
    number_of_boxes+=1;
  }
  else {
    number_of_boxes-=1;
  }
}
{% endhighlight %}

<canvas data-processing-sources="sketches/boxes.pde"></canvas>

## STRINGS
Strings are immutable and hence cannot be modified.
### Methods:
- toUpperCase()
- length()
- chartAt(x)
- equals(stringB) (This is used instead of `==` as `==` compares memory address, `equals` compares actual values at memory addresses)

### Specifying fonts:
To use a font in processing for display, you must initialize it using the following snippet of code:
{% highlight java %}
  PFont f;

  void setup() {
    f = loadFont("fontname")
    // or use
    // f = createFont("fontname", i, true/false) where i is the size, true/false enables/disables anti-aliasing
    textFont(f); // use font object 'f' to render text
  }

  void draw() {
    text(string,x,y); // (x,y)
  }
{% endhighlight %}

### Drawing text
`text(string,x,y)` is used to draw text, this is left-aligned by default, i.e. text starts being drawn from (x,y). `textAlign(LEFT)/textAlign(CENTER)/textAlign(RIGHT)` modifies this characteristic. `textSize(i)` specifies the size of the text. `textWidth(char)` returns the width of a specific character.
