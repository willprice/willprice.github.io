---
title: "Learning Processing: Arrays"
layout: layout
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
