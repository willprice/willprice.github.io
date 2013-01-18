---
title: "Processing and XMonad"
layout: post
---

After having put up with problems with the Processing IDE for quite a
while, I could no longer take not being able to focus the text area
without clicking on the stop button.

It transpires this is an issue caused by XMonad's handling of Java swing
applications as noted by Krzysztof Krason in a [thread](http://youtrack.jetbrains.com/issue/IDEA-65637)
in regard to the IDEA IDE (which also uses Java swing).

> It's not a problem with Intellij but with XMonad, it has problems with
> java swing applications.
> The solution is to use something like this in to add "import
> XMonad.Hooks.ICCCMFocus" and in your logHook add "takeTopFocus".

So the solution is remarkable simple. Just add these lines to your
xmonad.hs file:

{% highlight haskell %}
import XMonad.Hooks.ICCCMFocus

main = do
  import XMonad.Hooks.ICCCMFocus
  
  logHook = ... >> takeTopFocus 
{% endhighlight %}
