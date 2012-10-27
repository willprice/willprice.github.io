---
title: Learn you a Haskell Chapter 1 Starting out
layout: post
tags: [haskell, notes]
---

I've decided to learn Haskell as from what I've read, it seems like an
interesting language quite different from anything I've used before. I'd
also very much like to be able to hack on [XMonad](http://xmonad.org/),
the tiling window manager I use.

['Learn you a Haskell for great good'](http://learnyouahaskell.com/) is a fantastic book written in a
light hearted manner with very good explanations and drawings to keep
your attension. It's available to read free on the website.


### Haskell ###
Haskell is _referencially transparent_ and as such you can't
change variables (they're actually called _definitions_ or _names_ as they don't _vary_)after assigning a value; for example you can't say x = 5
and then saying that x = 6. This means _side effects_ don't exist (when
calling a function twice with the same parameters it might return
something different in an imperative lanuage -- not in Haskell! Variable
reassignment isn't permittted).

Haskell also has the cool property of being _lazy_ meaning it will only
evaluate expressions when it absolutely must, this allows us to play
with infinite sets, this is the result of referencial transparency.

Haskell is _statically typed_ meaning that Haskell knows what things are
numbers, strings, lists and so on. This allows it check for a lot of
possible errors at compile time. Whilst this might lead you to think
that you have to tell Haskell what type everything is in your program,
this is not the case. Haskell has a _type inference_ system that knows
that when you perform the assignment a = 5 + 4, that a is also a number,
and so on.

### Basic Operators ###
- AND: &&
- OR: ||
- NOT: not
- EQUIVALENCY: ==
- NONEQUIVALENCY: /=

- succ x: returns the _successor_ of x (e.g. succ 8 = 9)
- min x y: returns the _minimum_ of x and y (e.g. min 7 10 = 7)
- max x y: returns the _maximum_ of x and y (e.g. max 7 10 = 10)
- div x y: performs integer division on x and y (e.g. div 92 10 = 9)

Functions that take 2 arguments can be called as _infix_ operator like
so:
{% highlight haskell %}
ghci> div 92 10 
9
ghci> 92 `div` 10
9
{% endhighlight %}

#### Operator Precedence ####
The order in which operators evaluated from first to last is:

1. Functions
2. Multiplication and division 
3. Addition and subtraction

If operators are on the same level of precedence, for example the
expression:
{% highlight haskell %}
ghci> 7 * 8 / 4
14.0
{% endhighlight %}
operators are evaluated from __right to left__


### Function definition ###
Functions are defined in a very clean way in Haskell, like so:
{% highlight haskell %}
doubleMe x = x + x
{% endhighlight %}

_doubleMe_ is the function name, all the strings or characters after the name to the equals sign are parameters, parentheses are not used to bind parameters to functions like in C or Python. The expression after the equals sign is evaluated when the function is called and returned.

{% highlight haskell %}
ghci> doubleMe 7
14
{% endhighlight %}

Also remember that definitions are also functions so 'x = 8' is a function that returns 8 when called and so on.

### Conditionals ###
Given that Haskell isn't imperative all 'if's must be accompanied by an 'else', if the predicate evaluates to false then the function won't know what to return otherwise.
{% highlight haskell %}
amIawesome x = if x == "Keith Devlin"
                then "Yes"
                else "No, You're not Keith Devlin"


ghci> amIawesome "Keith Devlin"
"Yes"
{% endhighlight %}

### Lists ###
Lists are _homogenous_. Concatenation walks through the first list before appending the other list, this is computationally intensive on big lists. Prepend lists to avoid this issue.

{% highlight haskell %}
list = ["this","is","a","list"]
ghci> list
["this","is","a","list"]
{% endhighlight %}

{% highlight haskell %}
-- General list operations


-- Concatenation/Appending
ghci> [1,2,3] ++ [4,5]
[1,2,3,4,5]

-- Prepending
ghci> 1 : [2,3]
[1,2,3]

-- Accesing list elements (index starts at 0)
ghci> [12,13,14,15,16] !! 3
15

-- Head, Tail, Init and Last
ghci> head "hello"
'h'
ghci> tail "hello"
'ello'
ghci> init "hello"
'hell'
ghci> last "hello"
'o'

-- List comparisons (refer to notes above for explanation)
ghci> [3,2,1] > [2,1,0]
True
ghci> [3,2,0] > [3,1,100]
True
ghci> [3,4,2] == [3,4,2]
True
ghci> [4,4,4,2] == [4,4,4,4]
False
ghci> [3,2,1] < [2,3,100, 10]
False

-- Length
ghci> length [5,4,3]
3

-- null (is the list empty)
ghci> null []
True
ghci> null [1]
FalsE

-- Reverse
ghci> [1,2,3]
[3,2,1]

-- Take
ghci> take 3 [4,5,6,7]
[4,5,6]
ghci> drop 3 [4,5,6]
[7]
ghci> drop 10 [4,5,6]
[]
ghci> maximum [1,3,50,2,7,92]
92
ghci> minimum [1,4,0,7]
0
ghci> sum [5,4,3,2,1]
15
ghci> product [6,2,3]
36
ghci> elem 4 [3,4,5]
True
ghci> elem 2 [3,4,5]
False
ghci> 2 `elem` [2,3,4]
Truce

{% endhighlight %}

#### TEXAS RANGES ####
Texas ranges allow you to produce a list from an arithmetic sequence in any step size up to any number or it can even be infinite.
{% highlight haskell %}
ghci> [1..20]
[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
{% endhighlight %}

This shows a simple texas range, the default step size of 1, if you wanted to create an arithmetic list with a negative common difference then you must specify the step size as haskell defaults to one. so [20..1] would evaluate to an empty list as 20 is greater than one.

{% highlight haskell %}
ghci> [20,19..1]
[20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1]

-- Or you could always just reverse a list:

ghci> reverse [1..20]
[20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1]
{% endhighlight %}

As the above example shows, step size is implicitly defined by writing the second term of the sequence. 

Any type of element that is enumerable can be used with texas ranges. Letters for example are enumerable:

{% highlight haskell %}
ghci> ['a'..'z']
"abcdefghijklmnopqrstuvwxyz"
{% endhighlight %}

If you want to produce a list up to a certain number of members you can use 'take' on an infinite list:

{% highlight haskell %}
ghci> take 12 [6,12..]
[6,12,18,24,30,36,42,48,54,60,66,72]
{% endhighlight %}

'cycle' and 'repeat' produce infinite lists which can be used with 'take' to produce finite lists.

{% highlight haskell %}
ghci> take 9 (cycle [1,2,3])
[1,2,3,1,2,3,1,2,3]

ghci> take 10 (repeat 10)
[10,10,10,10,10,10,10,10,10,10]
{% endhighlight %}

#### LIST COMPREHENSIONS ####
List comprehensions are very similar to set comprehensions for mathematics (note: very cool). They allow you to generate lists of elements based on predicates. The example below will show a typical list comprehension:
{% highlight haskell %}
example xs ubound = [ x*2 | x <- xs, (x < ubound) ]

ghci> example [1..10] 5 
[2,4,6,8]
{% endhighlight %}

_example_ refers to the name of the function and the 2 variables afterward are the parameters: 'xs' 'ubound'. 'x' is drawn from the list 'xs', then the predicate 'x < ubound' filters out the elements of the list greater than 'ubound', finally the stripped list is then passed to 'x*2' where a new list is generated from the previous list x being mapped to x*2.

A better example:
{% highlight haskell %}
square xs = [x**2 | x <- xs]

ghci> square [1,2,3,4]
[1,4,9,16]
{% endhighlight %}

Of course list comprehensions can spiral in complexity so that you end up with expressions like:
{% highlight haskell %}
fizzbu

