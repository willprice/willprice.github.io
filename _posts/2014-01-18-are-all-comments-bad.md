---
layout: post
title: "Are all comments bad?"
---

I've been thinking about comments in code. Some people advocate not using
comments suggesting that your code should be self documenting. I believe this to
be a good practice where possible. If you need comments to explain what your
code is doing, then it's quite likely you're code isn't sufficiently broken down
into lots of little methods naming what each part does. What happens when you
have code that is simply non-intuitive and breaking it out into named methods
doesn't work?

Let's look at an example to emphasize my point. We'll take the naive Fibonacci
function:
{% highlight python %}
{% include code/python/fib/naive_fib.py %}
{% endhighlight %}

Now for a tail recursive implementation that is more efficient (but not in
Python, as it doesn't have tail call optimization! I should have done it in C,
but I couldn't face writing the tests using `check`). 

{% highlight python %}
{% include code/python/fib/tail_recursive_fib.py %}
{% endhighlight %}

I've tried my best to make this as self-explanatory as possible. I still feel
that additional explanation would help for whoever has to maintain it. The first
time I saw this definition `nth_fib` was `a` and `nth_minus_one_fib` was `b`, I
had absolutely no idea how it worked. Naming things really makes such a
difference!

The additional information I'd like to add is:

* We only return `nth_minus_one` if `counter == 1`, which implies we're calling
  `fib(1)` so we return the first fibonacci number: 0.
* When `n > 1` then `counter == 2` terminates the algorithm returning the
  accumulated value
* A few examples: 

        fib(3) -> fib_accumulator(3, 1, 0) -> fib_accumulator(2, (1 + 0), 1) -> return (1 + 0)

        fib(5) -> fib_accumulator(5, 1, 0) -> fib_accumulator(4, (1 + 0), 1) -> 
                  fib_accumulator(3, (1 + 0 + 1), (1 + 0)) -> fib_accumulator(2, (1 +
                  0 + 1 + 1 + 0), (0 + 1 + 1)) -> return (1 + 0 + 1 + 1 + 0) -> return 3

I think that information makes it clearer how the function works. I tried to
extract the base cases to add more explanation via code, but couldn't think of
descriptive enough methods, maybe that's because I don't grok the algorithm. I
can see how it works, but find it very hard to articulate how to explain it's
behaviour, when this happens I find it's best to resort to examples to guide
explanation, but this is difficult to do in code! Unit tests you scream!? True,
maybe I should add comments there explaining what is happening? How do you
handle cases where you feel your code isn't sufficiently descriptive, but can't
make it more descriptive through refactoring?
