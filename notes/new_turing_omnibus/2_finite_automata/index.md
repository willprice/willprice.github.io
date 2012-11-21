---
title: "Finite Automata"
layout: layout
---
Finite automata are computational models that consist of internal
circuitry that exist in a stable equilibriums in between signals 
being interpreted. There must only be a finite number of these equilibrium
states.

A finite automaton has a set of states Q, a set of input
signals Epsilon and a function epsilon mapping members of Epsilon (input
signals) to Q (set of states).

There are 2 special states in Q, the initial state and the final state.
The set of input signals that make the automaton reach the final state
from the initial state are said to be the _language of the
automaton_ which are expressed through regular expressions for finite
automata.

If there are a known number of states it is possible to precisely deduce
the language of the finite automaton (L_a) 

In regular expressions:
- `+` is used as an OR for example: 0101 + 1111 subset L_a means that
  either 0101 OR 1111 can be excepted by the finite automaton.
- `*` means 0 or more times: 01(001)* matches 01001, 01001001 and so on.


[finite automata](http://theoryclass.wordpress.com/2010/08/17/boundedly-rational-players/)
