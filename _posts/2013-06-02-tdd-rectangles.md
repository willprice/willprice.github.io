---
layout: post
title: "TDD rectangles"
description: ""
category: 
tags: ['maths']
---
[Jason](http://www.codemanship.co.uk/parlezuml/blog/index.php) and I had a
rather interesting pair programming session last week where we tackled a problem
that I found on [Topcoder](http://topcoder.com). It is in fact a slight twist
(easier) on the actual topcoder problem as I didn't have it to hand when we were
pairing.

The Problem:
------------

> Given a composite rectangle (composed of unit rectangles) of arbitrary dimensions, calculate the number of
> sub rectangles that can be composed from the unit rectangles. Remember squares
> are rectangles...

If that's not clear enough, this diagram should help articulate what the problem
is.

![Diagram of 2x2 rectangles and it's 9 subrectangles](/media/img/diagrams/tdd-rectangles/4x4-solution.svg)

Here we can see that you can create 9 rectangles from the initial 2x2 rectangle.

The Design:
-----------
Tackling this in a TDD-way we first had to decide on rough roadmap of
test cases. The simplest test case seemed to be a invalid rectangle,
0 rectangles high or wide, or both.

    Test cases:
    -----------
    1. Do not accept geometrically impossible rectangle

We'd then go on to a 1x1 rectangle, 1x2, 2x1, 3x1, 1x3, 2x2 and 3x2. Jason
stressed that we were just sketching out a path we _might_ take, it may not have
been neccessary to use all the test cases, or maybe we'd need more; the list
seemed like it would probably be sufficient for a full implementation.

The next step was to figure out how many subrectangles there were in each
composite rectangle, this involved a bit of drawing and tallying. In the end I
think I only miscounted one test case which we noticed fairly quickly when
coding.

    Test cases:
    -----------
    1. Do not accept geometrically impossible rectangle
    2. 1x1 has 1 subrectangle
    3. 2x1 has 3 subrectangles
    4. 1x2 has 3 subrectangles
    5. 3x1 has 6 subrectangles
    6. 1x3 has 6 subrectangles
    7. 2x2 has 9 subrectangles
    8. 3x2 has 18 subrectangles

Having written our roadmap it was now time to start tackling this problem. We
used Java, and JUnit with Eclipse.

The implementation up to 3x1 was fairly simple, however it started to get a little
more tricky after that stage, it wasn't immediately obvious what formula we
should have been using, `\(xy + (x-1)y + (y-1)x\)` seemed like a promising
start, passing all the previous tests up until that point, addition of another
term sounded like it might hold the solution, however it was difficult to think
of what it could be, we didn't come up with anything in the end.

Our design up until this point had been heading towards a solution in the form
of `return some_algebraic_formula`, we changed tack and started looking at it in
terms of combinations as we thought it might be a more successful avenue of
attack. Jason suggested it might be as simple as a factorial, given that there
are `\(^n C_r\)` ways of ordering `\(r\)` items from a sample of size `\(n\)`
and...
`\[^n C_r = \frac{n!}{r!(n-r)!}\]`
Maybe not as simple as a single factorial, but we were definitely dealing with
sequences and/or combinations. The problem with combinations is that they
calculate all possible combinations including non-contiguous options (think
first and last subrectangle of a 3x1). We didn't discuss this at the time
because a simpler solution presented itself.

![Diagram demonstrating how many of each size of subrectangle are present in a
3x1 rectangle](/media/img/diagrams/tdd-rectangles/combination-1.svg)

Being Test Driven in design, we looked at our current test case, a 3x1 rectangle
(I've illustrated a 1x3, imagine it's just rotated!), after a bit of drawing and
colouring it was evident that the number of subrectangles present in a column
decreased by 1 for each unit increase in subrectangle length (refer to diagram). 
In the general case you have `\(n + (n-1) + (n-2) + \ldots + 1\)` subrectangles
per column where `\(n\)` is the length of the column. We could iterate over each
column and add either the general result of this formula (`\(\Sigma_0^nr\)`), or
generate it on the fly with another loop. Initially it was simplest to just loop
over columns and rows separately, instead of trying to take the larger step and
implement the actual solution.

Our implementation now took the form:

{% highlight java %}
public long getSubrectangles() {
    long numberOfSubrectangles = 0;
    for (int i = 1; i <= x; i++) {
        numberOfSubrectangles += i;
    }
    
    for (int j = 1; j <= y; j++) {
        numberOfSubrectangles += j;
    }
    // We count the top left 1x1 rectangle twice with this method
    return numberOfSubrectangles - 1;
}
{% endhighlight %}

The next test case: 2x2, introduced a new class of rectangles, 2D, the others
had all been 1D in either the `\(x\)` or `\(y\)` axis. The previous
implementation yields 5 subrectangles instead of 9. We looked at which ones it
was counting, just the first row and first column -- time to loop over the whole
thing. Enclosing each loop with an outer loop iterating over either column or
row depending on the inner loop and removing duplicates was a possibility, a
very messy one, probably unlikely to succeed in being the general solution
either. The algorithm needed to loop over both columns and rows (a nested loop?)
and then calculate the number of possibilities, hopefully without counting
duplicates.

After a bit of trial and error we managed to reach the general solution:
{% highlight java %}
for (int i = 1; i <= x; i++) {
    for (int j = 1; j <=y; j++) {
        numberOfSubrectangles += i*j;
    }
}
{% endhighlight %}
I like this, it's rather clever. It's easiest to understand given an example,
let's use the 2x2 rectangle we were trying to solve. The first column has 3
subrectangles, here's what the code excecutes:

    i = 1:
        j = 1:
            numberOfSubrectangles += 1;
            // numberOfSubrectangles = 1;
        j = 2:
            numberOfSubrectangles += 2;
            // numberOfSubrectangles = 3;

Looping over the first column we get 3 subrectangles, so good so far.

    i = 2:
        j = 1:
            numberOfSubrectangles += 2
            // numberOfSubrectangles = 5
        j = 2:
            numberOfSubrectangles += 4
            // numberOfSubrectangles = 9

    return 9

Through the second column, the subrectangles found in `i = 1` are found again in
this next column, however, we also need to take into account the rectangles that
are formed along the rows, which there are 3 of, giving us a total of 6
additional subrectangles.

Algebraic solution:
-------------------
We had a solution! I like maths so I've found the algebraic solution from the
code. Reasoning about loops of loops in mathematics is particularly
aesthetically pleasing to me.
{% highlight java %}
for (int i = 1; i <= x; i++) {
    for (int j = 1; j <=y; j++) {
        numberOfSubrectangles += i*j;
    }
}
{% endhighlight %}

I'll be using `\(z\)` as the `numberOfSubrectangles`, it makes writing the maths
easier.
`\[\begin{aligned}
 z &= \sum_{i=1}^x (\sum_{j=1}^y(ij)) \\
 z &= \sum_{i=1}^x i(\sum_{j=1}^y(j)) \\
 z &= \sum_{i=1}^xi(\frac{1}{2}y(y+1)) \\
 z &= \frac{1}{2}x(x+1)\frac{1}{2}y(y+1) \\
 z &= \frac{1}{4}xy(x+1)(y+1)
 \end{aligned}\]`

You can literally change the Java code to return `\(z\)`, how pleasing :)

After tackling the problem with Jason, I had a go solving it mathematically a
few days after and by then I'd forgotten the solution; I didn't have much success at all.
In this case I think developing in this way helped us to reach the insight that
we should add `i*j` inside our nested loops. I don't have the problem solving
skills to incrementally build a solution mathematically, although I'm starting
to aquire them in the domain of programming (very slowly), perhaps if I try and
apply a TDD approach to maths I may get further with hard mathematical problems?
