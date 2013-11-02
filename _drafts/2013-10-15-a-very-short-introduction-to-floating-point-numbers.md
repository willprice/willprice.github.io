---
layout: post
title: "A very short introduction to floating point numbers"
---

If you don't like my post, head over to the Duke CS department's notes on
floating point numbers, they're well presented, and easy to understand!

[Duke floating point notes](http://www.cs.duke.edu/~raw/cps104/TWFNotes/floating.html)

# Motivation
In Week 3 of my programming & algorithms course we've been introduced to
floating point numbers. In essence the information we got given was:

> * Sign and magnitude
> * Mantissa has an implied lead 1
> * Exponent uses biased notation
> * Number = $(-1)^S \times (1 + mantissa\times 2^{-53})\times >   (2^{exponent-1023})$
> Range: 2.22507e-308 to 1.79769e+308 (+/-)

Helpful? Well... no, not really. Not even a little bit! I can do better!

# Prerequisites
You'll need to understand:
* [Scientific notation][http://en.wikipedia.org/wiki/Scientific_notation] - If
  you have seen things like $4.3215x10^4$ you'll be fine!
* [Binary](http://en.wikipedia.org/wiki/Binary_number)

# Basics
Floating point numbers are the computer's equivalent of real numbers, except
they suck for several reasons that I'll get into later. 

The general process:
1. Number $n$ is converted into binary $b$.
2. Binary number $b$ is converted into scientific notation.
3. Sign bit ($s$) calculated from sign of number.
4. Floating point exponent ($e$) calculated from real exponent.
5. Floating point mantissa ($m$) calculated from coefficient.

This is just something people invented. It's a logically way to do it, but
you're going to have to learn it, as you can't really derive it from first
principles (for those of you from maths, and not CS!).

# Converting a decimal into binary
This is a fairly simple process that you should have done several times before.
If not, head over to youtube, and find some videos showing you how to do this.
After that come back here, and I'll explain how decimal points with binary work.

Let's look at 232.03125, we'll convert that into binary
1. Convert the integer part 232 into binary:

        128 64 32 16 8 4 2 1
        1   1  1  0  1 0 0 0

2. Convert the decimal part into binary using the incredibly this incredibly
   useful algorithm:
   1. 
