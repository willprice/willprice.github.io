---
title: "Hello Recursion"
layout: layout
---

Recursion involves a self-calling functions. Lots of functions in Haskell should be written like this as it allows
for a very elegant representation of what a function does rather than how to compute it.

{% highlight hs %}
  -- Maximum function
  maximum' xs = case xs of [] -> eror "Maximum of empty list"
                           [x] = x
                           x:xs = max x (maximum' x)
{% endhighlight %}

When trying to define a function recursively, first start with the base case, then think about the algorithm in a trivial case and how that can be implemented in code, think about it abstractly, make sure all situations are covered.

Quicksort:
{% highlight hs %}
  -- this ones nice!
  -- quicksort only works on types which can be compared: i.e. are of the Ord type class
  quicksort :: (Ord a) => [a] -> [a]
  quicksort [] = [] -- base case

  -- using the first part of the list as the pivot
  quicksort x:xs = 
  let smallerOrEqual = [ a | a <- xs, a <= x]
      larger = [ a | a <- xs, a > x]
  in quicksort smallerOrEqual ++ [x] ++ quicksort larger
{% endhighlight %}

Ah beautiful.
