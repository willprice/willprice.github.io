---
title: "Haskell Type notes"
layout: layout
---

Use `:t` in GHCi to check the types of things, the return statements are _type signatures_ indicating the type of the thing you're examining. Type signatures for functions take the form: `func_name :: parameter_type -> return_type` where parameter_name might be `Bool` and return_type migh also be Bool (e.g. in the case of `not`)

When Haskell is given a function of an unknown type without a type declaration, it uses what it knows about parts of the function to reason what type the parameters and return value are. 

For example:
{% highlight hs %}
is3 numb = numb == 3
{% endhighlight %}

is3 takes a number and compares it to the number 3, if they're equal, then it returns True. So starting from the function definition, numb must be of type Number as it's being compared with an Int (which can be generalised to the Number class and compared with any other number), is3 finally takes on the result of numb == 3, which will result in a Bool, so the type signature is is3 :: Number -> 
