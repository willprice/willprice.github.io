---
layout: post
title: "Reservations on TDD"
---

# Algorithms
I've been playing around implementing algorithms using TDD. If you're
interested in which:
* Sieve of Eratosthenes
* Bubble sort
* Binary search 
* Soundex

I find that with some of these (Soundex in particular), TDD works very well to
design a coherent implementation, however I find TDD exceptionally difficult
with the sieve of Eratosthenes. The steps necessary to produce the simplest
solution for each test case aren't at all obvious to me. Why don't I just
implement the algorithm as I've got it in pseudo-code. I can get the pseudo-code
for all the algorithms; why not just convert this into whatever language I'm
using?

Perhaps struggling and finding the next simplest solution gives one a greater
understanding of the algorithm, and will help develop a deep intuition of
how the algorithm functions, and how it was developed (from particular cases to a
generalisation). Does the value of this outweigh that of the struggle involved
in changing the implementation?

The whole point of TDD is to triangulate around your solution, each test case is
meant to bring you closer to the general solution, but sometimes it's
exceedingly difficult to see how to make the jump from one case to the next
whilst still heading in the direction of your final solution. How do you deal
with this challenge? Do you just make a big step, and write your final solution,
and then add additional unit tests--this is not TDD, but is it a less valid
technique?  
