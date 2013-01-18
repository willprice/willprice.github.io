---
title: "Higher Order Functions"
layout: layout
---

When passing a function (f1) as a parameter to another function (f2), then f2 is a higher order function. Bizarrely every function in Haskell officially only takes one parameter :O! When you're using a function that takes more than one parameter, what happens is the first parameter is evaluated, the function returns ANOTHER function, which then takes the second parameter and creates another function which is then applied to the 3rd parameter and so on...

Functions that only take one parameter are called curried functions.

Infix functions can be turned into prefix functions by surrounding them by parentheses, this is called a _section_ (like the analog of putting back ticks around prefix functions turning them into infix functions)

Partial functions can be written like so `(/10) 9` or `(max 9) 1` 

Functions aren't members of _Show_ so they cannot be printed to the screen in a nice string format (which would be very cool.

Example of higher order function:
{% highlight hs %}
  addThree x = x + 3
  applyTwice :: (a -> a) -> a -> a
  applyTwice f x = f (f x)

  ...

Prelude>  applyTwice addThree 2
8
prelude> applyTwice (+1) 1 -- remember that (+1) is a sectioned function, and therefore (+1) :: (Num a) => a -> a
3
{% endhighlight %}

Some more interesting functions:
{% highlight hs %}
  filter' :: (a -> Bool) -> [a] -> [a]
  filter' _ [] = []
  filter' f (x:xs)
      | f x = [x] ++ filter' f xs
      | otherwise = filter' f xs

  flip' :: (a -> b -> c) -> (b -> a -> c)
  flip' f = g
    where g x y = f y x

  map' :: (a -> b) -> [a] -> [b]
  map' f [] = []
  map' f [x] = (f x):[]
  map' f (x:xs) = f x : map' f xs
{% endhighlight %}

Let's code a function that will generate a Collatz chain from a starting number. A Collatz chain is defined:

- start with any natural number
- if the number is 1, stop
- if the number is even, divide it by 2
- if the number is odd, multiply it by 3 and add 1
- repeat the algorithm with the resulting number

{% highlight hs %}
  collatz :: (Integral a) => a -> [a]
  collatz a
    | a == 1      = [1]
    | even a      = a:collatz (a `div` 2)
    | odd a       = a:collatz (3 * a + 1)
    | otherwise   = []
{% endhighlight %}

Remember that `div` must be used for Integral division, otherwise a Rational number will be the result, which can't be used with `even` and `odd`.
# Folds
Folds are pretty cool, they allow you to apply a binary function to every member in the list starting with the first and second value, then the result of that and the third value and so on, the starting value is called the _accumulator_. 

Folds deal with reducing a data structure down into a single value, this is carried out through a recursive process

{% highlight hs %}
  -- Definition of foldl' (fold left)
  foldl' :: (a -> a -> a) -> a -> [a] -> a
  foldl' f acc [x] = f acc x
  foldl' f acc (x:xs) = foldl' f (f acc x) xs
{% endhighlight %}

Implementing the sum function can be done recursively or with foldl:
{% highlight hs %}
  -- recursive definition
  sum' :: (Num a ) => [a] -> a
  sum' [x] = x -- base case
  sum' (x:xs) = x + sum xs
  
  -- foldl definition
  sum' :: (Num a) => [a] -> a
  sum' xs = foldl (+) 0 xs
{% endhighlight %}

`foldr` is similar to `foldl` but starts from the right, rather than the left and it has a different syntax:
`foldl <binary function> <initial accumulator val> <list>`, the binary function (f) will be applied like so: `f acc x` where `x` is the current val being read from the list, and `acc` is the accumulator.

Looking back at `foldr` you apply it in the same way as `foldl`: `foldr <binary function> <initial accumulator val> <list>`, however, when the binary function is evaluated, it's parameters are flipped: `f x acc`. This might seem confusing at first, but there's logic to it: when you're reading a list from the right, you're going right to left, so the accumulator is generate from all the stuff you've just read, which is on the right, whereas when you're reading a list from the left, all the stuff you've read was on the left, hence why the accumulator comes first!

# Lambda functions
Anonymous functions are simply functions that don't have a name, these are especially useful when dealing with higher order functions, as instead of writing a separate simple function, you can integrate it with function call. Let's have a look at an example where we define a separate function and the corresponding use of a lambda function. First off, lambdas are defined using `(\<arguments> -> <function body>)`, arguments are separated using commas, `\` simply says we're now defining a lambda function, the brackets just hold everything together.

{% highlight hs %}
  -- Using a where definition
  reverse xs = foldl appendList [] xs
    where appendList acc x = x:acc

  -- Using a lambda function
  reverse xs = foldl (\acc x -> x:acc) [] xs
{% endhighlight %}

# Syntactical beauty
## Function application with `$`
{% highlight hs %}
  ($) :: (a -> b) -> a -> b
  f $ a = f a
{% endhighlight %}
Yes, that's right, this does not modify the function at all. However it changes how an expression with `$` is evaluated, `f $ a + 4` would be evaluated as `f (a+4)`, `$` has the lowest precedence of all operators. This allows you to write code a little more cleanly without so many parentheses. For example: `sum (map (*2) [1..10])` becomes `sum $ map (*2) [1..10]`.  It also allows you to weird things like `map ($ 3) [(4+), (4*), (4/)]` strange, eh?

## Function composition
{% highlight hs %}
  (.) :: (b -> c) -> (a -> b) -> a -> c
  f . g = \x -> f (g x)
{% endhighlight %}

Yay, more abstraction! Cool things like `map (negate . abs) [1, -2, -4, 3]` are now possible. So function composition takes 2 functions and returns a composite function which can then be combined with more functions to make more complex composite functions f(g(h(i(x))))) == f . g . h . i, much tidier, and no nasty parentheses!

Note: Function composition is right associate, that is: `sum . tail` == `sum (tail)` 
  
What about using functions that take multiple parameters? well how about...
{% highlight hs %}
  -- not too tidy
  f x y = sum (replicate 5 (max x y))
  
  -- much better!
  f' x y = sum . replicate $ max x y
{% endhighlight %}

