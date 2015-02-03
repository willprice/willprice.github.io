---
title: Maths
layout: layout
---
# Maths
## Algorithms
### Stable Roommate problem

#### Terminology
* *stable matching*: A solution where everyone is paired in such a way that no
  two roommates would prefer to be together, than in their current match.

```
INPUT: a map of roommates to their strict preferences
OUTPUT: a map of roommates to their best match if possible, else nothing

while there are unmatched people do:
    let 'proposer' be the earliest roommate in the input that hasn't been
    matched.

    'proposer' proposes to the highest preference roommate, the 'recipient', in
    his preferences that hasn't already rejected him.

    if the 'recipient' has not received a proposal before then:
        the 'recipient' accepts the 'proposer'
    else if the 'recipient' prefers the 'proposer' over her current match then:
        the 'recipient' accepts the 'proposer'
    else:
        the 'recipient' rejects the 'proposer'

for all accepted proposals ('proposer' -> 'recipient'):
    reject all pairings where ('recipient' -> 'other_person') and 'other_person'
    has a lower ranking preference in the 'recipient's preferences compared to
    'proposer'.

for all cycles ('person_1', ... , 'person_n') and associated second preferences
('second_pref_1', ... , 'second_pref_n'):
    let 'second_pref_i' be the second preference of 'person_(i-1)'
    for all pairs ('person_(i+1)', 'second_pref_(i)'):
        'second_pref_i' rejects 'person_(i+1)'
```

While this pseudo code may be a little obtuse at first, you may find that in
addition to simple English description of how to perform the algorithm by hand
the algorithm will become quite clear in how it works.

We split the algorithm into three phases:

1. Gale-Shapley algorithm.
2. Remove lesser preferences from recipients.
3. Eliminate remaining preferences by analysis of cycles.

#### Rejecting a proposal

By rejecting a proposal `A -> B`, you must cross off both `B` in `A`s
preferences and `A` in `B`s preferences. In other words, every rejection
consists of removing two preferences from the preferences table.

#### Phase 1: Gale-Shapley algorithm

The Gale-Shapley algorithm was designed for a very similar problem to the
finding a stable matching for roommates, but instead of roommates the population
was split into two halves, males, and females, each of whom had their own
preferences. Only one gender would propose to the other to find a stable
matching.

We apply this algorithm to the roommates and their associated preferences. 

1. Pick the first roommate on the list that hasn't had one of their proposals
   accepted, we shall call her the *proposer*
2. The *proposer* proposes to her first preference, the *recipient*, that hasn't already rejected
   her. If the *recipient* hasn't had a proposal before, then he accepts,
   otherwise if the *proposer* is of a higher preference to the *recipient* than
   the *recipient* current match, the *recipient* accepts the proposal and
   reject his previous match.
3. Go to 1 whilst there are still unmatched roommates.

#### Phase 2: Removing lesser preferences

For every accepted proposal where *proposer* has been accepted by *recipient*,
reject all lower preferences then the *proposer* in the *recipients* preference
list

#### Phase 3: Eliminating remaining preferences by analysis of cycles

For every roommate that has more than one preference left in the preferences
table, write down a table where the top element is the roommate, and the one
below it is the 2nd preference of the roommate, then the next top element is the
last preference of the element one cell below and behind. Essentially in
constructing the table:

1. Fill in the cell below you current position with the 2nd preference of the
   current element
2. Fill in the cell to the upper right of your current position with the last
   preference of the current element

Or in other words: to go down, put the 2nd preference, and to go diagonally it's
the last preference.

Continue constructing the table until you reach a cycle in the top row. Then
reject all diagonal pairs (bottom left to upper right).

You should end up with a preferences table where each roommate has a single
preference

#### Exceptions

If you find that a roommate is rejected by everyone in a set of an even number
of roommates, then there will be no stable matching.
