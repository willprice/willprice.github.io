---
title: "Believe the type"
layout: layout
---


# Type classes:
- _Eq_: Any objects that can be compared for equality
- _Ord_: Any objects that can be ordered
- _Show_: Any objects that can be shown as a string (most types bar functions) (show :: (Show a) => a -> String)
- _Read_: Any objects that can be shown as a string ( read :: (Read a) => String -> a)
- _Enum_: Any objects whose value can be enumerated (anything a/b you can use in [a..b]
- _Bounded_: Int, Char, Bool 
- _Num_: Int, Integer, Float, Double
- _Floating_: Float, Double
- _Integral_: Int, Integer


Types can be instances of multiple type classes as some type classes cover subset of other type classes.
