---
layout: layout
---
# Avoiding obstacles
You've learnt lots! We've covered all the functions in the library, you can
bring all this functionality together to make an obstacle avoiding robot. I've
purposefully left this very open ended. I shall give you an example of some code
I wrote to do obstacle avoidance, it's not very good, please improve it! Better
yet define some new heuristics and try them out!

{% highlight c %}
{% include code/dfrduino/dfrduinoExampleObstacleAvoider/dfrduinoExampleObstacleAvoider.ino  %}
{% endhighlight %}

A few tips:

* Break all your complex behaviour into functions, as you can see I've got
  `lookLeft` and `lookRight` to get the distance when looking left and right.
* Use the serial port to print out values when you're not sure why your robot is
  doing something unexpected
* Tilting the head down can cause the IR sensor to pick up the floor, you may or
  may not want this; it could be part of quite a good heuristic.
