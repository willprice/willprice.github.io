---
title: "Regular Languages"
layout: layout
---

Pumping lemma - given a sufficiently long word from a regular language, pumping it will result in a new word in that language.

WTF is pumping? Pumping is the process by which a subword of a word is either removed (negatively pumped) or duplicated (positively pumped)
For example, given a word: W=XYZ, pumping W using the subword Y results in: W'=XYYZ, pumped again: W''=XYYYZ and so on.

Given a finite automata A, with n number of states, any word with length >= n accepted by the automaton will have to go through some sort of 
loop in states, which means that with that word we pump the looping subword to produce a longer word that will be accepted by the automaton
and hence will be part of that language.

The *pigeonhole principle* states that if more than n pieces of mail are delivered to n pigeonholes, then at least one pigeonhole receives 
more than one peice of mail.

The pumping lemma is useful for showing that languages are not regular, for example, let L be the language consisting of all palindromes
over the alphabet [a,b],  given the word W=a^n b a^n  
