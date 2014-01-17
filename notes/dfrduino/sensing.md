---
layout: layout
---
# Sensing the world around you!
Our robot is equipped with two types of sensors:

1. 1 x InfraRed (IR) distance sensor.
2. 3 x Line following sensors.

We'll be using just the first today. I haven't used the line following sensors
yet so there are no functions to use them in the `DFRduino` library. To measure
the distance we can use the `readDistanceInCentimeters()` function, can you
guess what it does...?

Ha... here's an example:
{% highlight c %}
{% include code/dfrduino/distanceRead/distanceRead.ino %}
{% endhighlight %}

Pick your robot up and point it's eyes (the IR sensor) at some stuff, see how
far, and how close it measure. Notice what happens when you move your hand too
close to the sensor, what happens to the distance read?

The IR sensor works by pulsing a infra red light then waiting to see how long it
takes to bounce of a surface and be read by the infra red sensor. Can you
explain what happens when you cover up the left hand side of the sensor?

Our goal at the end of the workshop is for you to have built an obstacle
avoiding robot. Let's have a look at how we can move depending on the distance
read by the sensor:

{% highlight c %}
{% include code/dfrduino/reverseAndRightIfObstacle/reverseAndRightIfObstacle.ino %}
{% endhighlight %}

Surprisingly, at least in my room this is a relatively effective tactic, in
fact, it's even better than some considerably more complex code I wrote! But
we'll look at the complicated code anyway, so you can show me how I was doing it
wrong all along! The method of going back for a second, then turning 90 degrees
right is called a *heuristic*. A *heuristic* is a way of solving a problem, it
will not give you the optimal solution (notice how the robot will not see things
below it's line of sight, like a pen, and will crash into them), but it will
give you a reasonable solution none the less. I'm sure you can develop a
heuristic that is superior to this demo. Go have a go doing that now...

... or if you're more interested in making your robot's head move, then move on
to the next section: [**nodding**](nodding.html) 
