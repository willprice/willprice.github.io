---
layout: layout
---
# Nodding and moving your robot's head
Notice how your robot's IR sensor is mounted on a frame that can move in 2
planes? Try moving it with your hand, don't be too vigorous with them, they're
rather flimsy and plastic!

So it's all well and good moving the head by hand, but it would be much more
userful doing this programmatically. There are two [servo
motors](http://youtu.be/bMXx25Q5s24) attached to each bracket, allow 180 degrees
of control. We can make the robot look left and right; and up and down, so let's
do just that:

{% highlight c %}
{% include code/dfrduino/nod/nod.ino %}
{% endhighlight %}

You may find that your robot's head isn't pointing forward, so we can modify the
sketch above to do that using `setHorizontalHeadPosition`, this works as you'd
expected, unlike `setVerticalHeadPosition`: 

* 0 degrees   - Right
* 90 degrees  - Centre
* 180 degrees - Left

{% highlight c %}
{% include code/dfrduino/nodCentral/nodCentral.ino %}
{% endhighlight %}

We could do something more interesting...

{% highlight c %}
{% include code/dfrduino/lollingHead/lollingHead.ino %}
{% endhighlight %}

See if you can figure this out by reading the code, If not, read on!

1. Set `x = 0`, `y = 0`.
2. Each time we loop check to see if `x > 180` or `x < 0`, if this is the case,
   then change the sign of `xIncrement` (so we either increase, or decrease our
   angle)
3. Each time we loop check to see if `y > 160` or `y < 0`, if this is the case,
   then change the sign of `yIncrement` (so we either increase, or decrease our
   angle)
4. Add `xIncrement` to `x` and add `yIncrement` to `y`.
5. Set our angles by `x` and `y`.
6. Delay for 20ms, this gives our servo a bit of time to move 1 degree. Play
   around with this value, see how fast it can go before it doesn't operate
   correctly. Can you explain what happens when you leave the delay out?

Time to move on and use everything you've learnt to [write an obstacle avoidance
program for your robot](avoiding.html)
