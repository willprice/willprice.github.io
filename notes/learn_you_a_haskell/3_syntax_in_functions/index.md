---
title: "Syntax in Functions"
layout: layout
---

# Pattern Matching
{% highlight hs %}
  factorial :: Int -> Int
  factorial 1 = 1
  factorial n = n * factorial(n-1)
{% endhighlight %}


All cases must be covered, using a placeholder at the end of the function definition will cover all other possible
cases. Cases are checked from top to bottom of function definition, so the wildcard entry should be at the bottom.


{% highlight hs %}
  charName :: Char -> String
  charName 'a' = "Albert"
  charName 'b' = "Billy"
  -- x acts as a universal matcher and will match anything
  charName x = "Sorry, I don't know what that is"
{% endhighlight %}


This wildcard matching pattern works very well as you can define functions very cleanly:


{% highlight hs %}
  addVectors :: (Double, Double) -> (Double, Double) -> (Double, Double)
  addVectors (x1,y1) (x2,y2) = (x1+x2, y1+y2)
{% endhighlight %}


`_` represents a generic variable in function definitions, something that we don't care about.


{% highlight hs %}
  head' :: [a] -> a
  head' [] = error "Can't call head' on an empty list"
  head' ( x: _ ) = x -- there should be no spaces between the x and underscore, this is to fix md rendering
{% endhighlight %}


`++` is used for concatenation of lists


# As Patterns
As patterns allow you to refence a whole list easily when you've broken it down into constituent elements in a function
definition. Syntax: `name@(list)`, name is used to refer to the `list`, and `list` is usually written like `x:y:xs`, allowing
easy access to the first and second items of the list.


{% highlight hs %}
  firstLetter :: String -> String
  firstLetter "" = "Empty string, whoops!" -- Match any empty strings
  firstLetter all@(x:xs) = "The first letter of " ++ all ++ " is " ++ [x]
{% endhighlight %}


# Guards
Guards are used for checking whether parameters satsify some predicate, they're like having a whole load of if and else
statements, just must much prettier, `|` marks the start of a guard, `\n` ends it:


{% highlight hs %}
  bmiTell :: Double -> String
  bmiTell bmi
    | bmi <= 18.5 = "You're underweight"
    | bmi >= 30.0 = "You're fat"
    | otherwise = "You're intermediate"
{% endhighlight %}


Here `otherwise` is used (It's a wildcard matcher) and will handle anything that doesn't match the predicates above it.
Guards are evaluated like patterns, from top to bottom.


# Storing intermediate results
## Where
In python you'd calc something once like: `x = x * 10.0/13.0`, then use x for all our further calculations. Haskell
doesn't have variable, only functions, or only immutable variables, depending on how you want to think of it.


{% highlight hs %}
  bmiTell :: Double -> Double -> String
  bmiTell weight height
    | bmi <= skinny = "You're underweight, you emo"
    | bmi <= normal = "You're supposedly normal"
    | bmi <= fat = "You're fat!"
    | otherwise = "Blimey, surgery needed ASAP"
  where bmi = weight/height^2
        skinny = 18.5
        normal = 25.0
        fat = 30.0
{% endhighlight %}


It's very simple really, don't overcomplicate it in your head. Just make sure all vars are located in same column like above.
The vars lexical scope is the function.


## Let expressions
let expressions are very local, they're pretty much self-contained: `let <bindings> in <expression>`, they can be used anywhere
other expressions can be used. The use of `where` just binds values to names whereas `let` actually is an expression itself.


{% highlight hs %}
  calcBmis :: [(Double, Double)] -> [Double]
  calcBmis xs = [ bmi | (w,h) <- xs, let bmi = w / h^2, bmi > 25.0]
{% endhighlight %}


## Case expressions 
case expressions follow the pattern:
{% highlight hs %}
  case express of pattern -> result
                  pattern -> result
                  pattern -> result
{% endhighlight %}


A more concrete example:
{% highlight hs %}
  describeList :: [a] -> String
  describeList ls = "The list is " ++ case ls of [] -> "Empty."
                                                 [x] -> "Singleton list"
                                                 xs -> "Long list."
{% endhighlight %}

