---
layout: layout
---
# Moving your robot
I should imagine you'll probably want to get your robot moving, no? Well
let's see how to do that:

{% highlight c %}
{% include code/dfrduino/moving/moving.ino %}
{% endhighlight %}

Compile and upload the code to your robot, hopefully it should go
forward. Now, if your robot is anything like mine (I hope it isn't, it's
had many many problems!) it may drift to the left, or perhaps to the
right. Now the function `setDirection` is not of much use as you can't
compensate for this hardware asymmetry. You'll have to write your own
function that replicates `setDirection` to make your robot go straight.
To set the speed of the left and right motors, I've provided you with
another function called `setMotors(int left, int right)`. Here I show
*my* version of `setDirection`:

{% highlight c %}
{% include code/dfrduino/setDirection/setDirection.ino %}
{% endhighlight %}

You can set your motor power between -100 (maximum speed backwards) and
100 (maximum speed forwards).

If you're not comfortable with `switch` statements, you could have 4
separate functions that do forward, backward, left, and right instead.

{% highlight c %}
// Write four functions like this
void setMotorsForward() {
  robot.setMotors(100, 90);
}
{% endhighlight %}

It's up to you which style you prefer, I have a slight preference for
keeping very similar behaviour all within one function.

Now you've written a function to get your robot moving, or perhaps your
robot works perfectly fine and you didn't need to write any of your own
functions, we can start making the robot do something a little more
interesting. 

Let's make the robot trace out a square on the floor. 

{% highlight c %}
{% include code/dfrduino/square/square.ino %}
{% endhighlight %}

As you may have noticed when modifying `timeTakenToMoveNinetyDegrees`
your robot will have traced out different polygons on the floor. Your
robot wouldn't have been turning 90 degrees, it would have been more or
less, so it might have traced out octagons (if you had very uncharged
batteries) or maybe even a triangle with charged batteries.

Take some time to play around with the functions I've provided you:
`setMotors` and `setDirection`; and any you have written yourself like
`mySetDirection`. 

Once you're comfortable directing your robot you should move on to
[**sensing**](sensing.html).
