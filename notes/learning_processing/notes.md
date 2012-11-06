---
title: "Learning Processing: Arrays"
layout: layout
---
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

<script src="/scripts/processing.js"></script>
<canvas data-processing-sources="test.pde"></canvas>
