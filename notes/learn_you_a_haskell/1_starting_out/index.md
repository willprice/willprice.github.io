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
False

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
