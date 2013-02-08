---
layout: post
title: "Beginner's steps with TDD"
description: ""
category: 
tags: []
---

[Jason Gorman](http://www.codemanship.co.uk/parlezuml/) has agreed to mentor me
in the subject of TDD (Test Driven Development). I plan to document my progress
as I learn the principles behind this philosophy.

TDD can be roughly outlined as follows:
- Write a failing test for the desired functionality.
- Write the smallest amount of code that can make _that_ test.
- Refactor you code, making sure your changes don't break functionality (keep
  running the tests)

As my first introduction to TDD Jason and I did some pair programming where I
implemented a simple Fibonacci function, this enabled me to see how the general
principle worked: "Test a little, program a little", and see what sort of
obstacles I might come across, such as "What's the next test going to be where
there is no linear path to follow". 

I've given my self a quick crash course in _git_ to document my progress, I can
commit every time I write a test or a piece of code. The history of the code
can be viewed using `gitk filename` using a GUI or `git log --follow --all -p
filename`[1].

I don't have the commit history for the _very_ first Fibonacci sequence exercise
I did, however I've got my third attempt at it (it's  pretty similar to the
first, I've just been trying to internalize the concepts I've met so far).

{% highlight diff %}
{% include fibonacci.log %}
{% endhighlight %}

You might disagree with my steps, or marvel at my crap commit messages; I'm just
getting started with the tools and methodologies so hopefully in 6 months time
I'll be able to look back at this and correct all my mistakes.

[1] - '--follow' handles renames, '--all' shows commits on all branches, '-p'
shows the changes in patch form (otherwise you just get commit messages)
