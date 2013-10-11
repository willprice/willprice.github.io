---
layout: post
title: "First weeks of university"
---

Having settled in here at Bristol, I've started my lectures, topics include:

* Mathematical methods for computer scientists
  * Logic
  * Objects
  * Proofs
  * Counting & Probability
  * Analysis
  * Linear Algebra
  * Probability & distributions

* Programming and Algorithms:
  * Learning C
  * Probably some algorithms too... 

* Introduction to Computer Architecture

  From Boolean logic to RAM and ROM (for the first half of this year, not sure
  what comes next)

* Origins of Computer Science

  From early machines through various programming languages, and OSes to the
  future of computer science.

## Evolutionary design and Waterfall
In a programming and algorithms lecture, waterfall was mentioned as the
development technique, and evolutionary design was said to be a bad way of
building systems. This came with the suggestion that systems should be
redesigned from the ground up when a system had sufficiently solved the problem
addressed. Jason vehemently opposed this view, saying evolutionary design was
about the only way to design programs as requirements are forever changing. He
said the key too succeeding was to continuously refactor your code to stop cruft
from encroaching on your software.

## Pairing
Jason and I also discussed what sort of problems we could tackle whilst
pairing. He suggested that we try and TDD algorithms, next week we'll be doing
*bubble sort*, and *binary search* in C. This week I'm going to try and get up
and running with C testing frameworks. So far I've had a look at:
* [Check](http://check.sourceforge.net/)
* [Minunit](http://www.jera.com/techinfo/jtns/jtn002.html)

I haven't managed to get either of these working yet. Check suggests the use of
autotools--something I haven't learnt yet. Minunit throws a segfault when I try
and compile my test code. Currently I'm leaning towards minunit for it's
simplicity.

Eric Radman has a good post on [unit testing C](http://eradman.com/posts/tdd-in-c.html). 
I haven't looked into it too deeply yet, as my knowledge in C is rather limited.

If TDDing algorithms is a good exercise we'll try and compile a wiki where we
explain the algorithm, and show the steps to a TDD implementation.

## Screen recording
Next week we'll record our pairing session and put it on youtube. I'm using 
[SimpleScreenRecorder](http://www.maartenbaert.be/simplescreenrecorder/) to
capture the screen and audio. It's a lot better than Gtk-RecordMyDesktop. I also
tried to check out [FreeSeer](http://freeseer.github.io/), however I couldn't
get it to compile.

## Apprenticeships as a complement to a degree
Jason feels confident that what I'll learn in my degree will not overlap too
much with what he wishes to teach me. Hopefully an apprenticeship will cover the
more practical aspects of software development that seem to take a backseat in a
CS degree, and understandably so given that it is CS, and not software
development. The problem is that most CS graduates will just go on to do
software development, and so it might not be a bad idea for CS students to learn
a decent amount of software development too. It looks as if we'll learn agile in
the 2nd year... I would have thought by then it'd be too late...
