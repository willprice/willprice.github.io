---
layout: post
title: "DCG object level representation in prolog"
---

Prolog is an excellent language for writing parsers using Definite Clause
Grammars (DCG) which are supported as first class objects in the language. The
language provides syntactic sugar to make writing these grammars more easily
than without.

Writing a DCG isn't far off translating a given grammar into prolog syntax, but
before we get to that we'll first look at writing DCGs the hard way without
syntactic sugar. It's important to understand the object level representation
of a DCG as this is what prolog actually executes.

Parsing a sentence using a DCG makes use of a standard prolog programming
pattern: [the difference
list](https://www.cl.cam.ac.uk/teaching/0809/Prolog/Prolog08ML5R2.pdf). The
*difference list* programming pattern represents a list `L` as the  difference
between two other lists `L1` and `L2` where `L2` is a sublist of `L1` and
`append(L, L2, L1)` (that is, `L` appended with `L2` forms `L1`).

A list in difference list form is represented by two lists. Let's say we want
to express `L = [element1, element2, ..., elementN]` in difference list form.
We need two lists `L1` and `L2` in which we'll encode `L` as the difference
between those lists. We'll represent the two lists as a pair, pairs in prolog
use the syntax `A-B` where `A` is the first element of the pair, and `B` the
second. This is not necessary, and later we'll drop the pair syntax and just
use arguments to hold each of the lists. Getting back to encoding `L` using
`L1` and `L2` we can form the difference list `L1-L2 = [element1, element2,
..., elementN | Rest]-Rest`. `L1` is `L` prepended to `L2`, and `L2` is some
other list, we don't really care what.

"Why do this, you're insane!?" You might ask, well we now have
a handle `Rest` on the end of the list which allows us to do some clever tricks
to write efficient predicates, and it makes writing parsers super
easy.

## Appending with difference lists

One of the simplest examples of the difference list pattern is an
implementation of the `append/3` predicate. You may have seen the naive
implementation:

```prolog
append([], L, L).
append([Head|Tail],List,[Head|Rest]) :- append(Tail, List, Rest).
```

However this takes linear time in execution... for something as frequently used
as appending, this isn't good enough, we want constant time execution! To achieve
constant time execution of appending we'll implement `append/3` using difference lists.

Let's start with a simple example, appending `[1, 2, 3]` to `[4, 5, 6, 7]`.
First lets convert these to difference list representation: `[1, 2,
3 | Rest1]-Rest1`, `[4, 5, 6, 7 | Rest2]-Rest2` (suspend your suspicion that this is
a pointless, useless representation, we'll get there!). What should the result
of appending the two lists result in (in difference list form?)? Well it should
at least start with `[1, 2, 3, 4, 5, 6, 7 | Something]-Something` as this contains the
result, but how about the `Rest` part of the list which we've left as
`Something`? I suppose we could put anything here but there's an alternative
that makes a bit more sense: reuse the `Rest` part from the second list, this
makes a bit more sense, as we preserve more information about our inputs this
way. In conclusion we've decided that appending the difference lists `[1, 2,
3 | Rest1]-Rest1` and `[4, 5, 6, 7 | Rest2]-Rest2` should result in `[1, 2, 3,
4, 5, 6, 7 | Rest2]-Rest2`.

How we write `append/3` such that it uses difference lists? Lets distinguish it
from the recursive definition we presented above my denoting it as `dappend/3`
(for difference-list append). We know the inputs, so they form the first
2 arguments of the predicate, and the last argument will be the appended
difference lists. Let's sketch this out: 

```prolog
dappend([L1element1, L1element2, ..., L1elementN | Rest1]-Rest1,
        [L2element1, L2element2, ..., L2elementM | Rest2]-Rest2,
        [L1element1, L1element2, ..., L1elementN, L2element1, L2element2, ..., L2elementM | Rest2]-Rest2]).
```

We could write out a bunch of predicates for all different sizes of lists, but
that'd be insanity! Instead we can make clever use of the `Rest` parts of the
difference lists to combine them!

```prolog
dappend(L1-Rest1, L2-Rest2, L1-Rest2) :- Rest1 = L2.
% or more simply:
dappend(L1-L2, L2-Rest, L1-Rest).
```

By unifying `Rest1` with `L2` we force the difference part of the `L1`
difference list to be the `L2` difference list. Going back to our example, we
unify `Rest1` in `[1, 2, 3 | Rest1]-Rest1` with `[4, 5, 6, 7 | Rest2]` resulting in
`[1, 2, 3, 4, 5, 6, 7 | Rest2]`, then make this into a difference list by lifting
it into the pair functor `-/2` in the output argument `[1, 2, 3, 4, 5, 6,
7 | Rest2]-Rest2`. No recursion, just unification!

Now what if we want to wrap this up so we don't have to use difference lists
directly? Let's try and write a wrapper `my_append/3` that takes 2 normal lists
`L1` and `L2` and concatenates them to form `L`, first we have to convert `L1`
and `L2` into difference lists, then we can call `dappend/3` and pull out the
difference of the result to get `L`.

```prolog
diff_list([], End-End).
diff_list([Head|Rest], [Head|DiffListRest]-End) :-
  diff_list(Rest, DiffListRest-End).

my_append(L1, L2, L) :-
  diff_list(L1, DiffList1),
  dappend(L1-_, L2-_, L-[]).
```

And some examples using `dappend/3` and `my_append/3`:

```prolog
?- L2 = [4, 5, 6], dappend([1,2,3|L2]-L2, L2-[], L-[]).
L = [1, 2, 3, 4, 5, 6].
% We force the difference list representing `L1` to be the
% difference between L1 appended to L2.

?- dappend([1, 2, 3]-_, [4, 5, 6]-[], L-[]).
L = [1, 2, 3].
% By failing to create a proper difference list in the L1 position, namely
% `[1, 2, 3]-_`, `_` unifies with `[4, 5, 6]` and L unifies with `[1, 2, 3]`.
```


To make the normal lists into difference lists we have to traverse them to the
end... defeating the whole object of the exercise: to make `append/3` work in
constant time, so DON'T use this unless you already have your lists in
difference list form.

Exercise: Take a few example difference lists and try appending them with the
`dappend/3` predicate. 


## DCGs: Grammars with difference lists

You should now be familiar with the concept of difference lists from the
`dappend/3` example. We now show how to construct parsers from difference
lists. What does it mean to parse a sentence? How are we going to represent
a sentence? What does it mean to partially parse a sentence? Keep these
questions in mind.

Prolog represents sentences as lists of words, an example being `[hello, my,
name, is, will]`. How about parsing this sentence? To parse it, we need
a grammar. A grammar specifies the legal sentences in the language; we'll constrain
our language to be sentences of the form `hello my name is <name>` where
`<name>` is either `will`, `tom`, or `henry`.

Lets define this in [EBNF](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form),
a standard form for representing grammars.

```
sentence = greeting, introduction;
greeting = "hello";
introduction = "my", "name", "is", name;
name = "will" | "tom" | "henry";
```

What are the valid sentences represented in Prolog?

```
[hello, my, name, is, will]
[hello, my, name, is, tom]
[hello, my, name, is, henry]
```

Parsing the sentence top-down from `sentence` involves substituting the LHS of
a rule for the RHS repeatedly until all non-terminals are replaced with
terminals. `[hello, my name, is will]` parsed by the rule `sentence` takes the
following sequence:

* `[], sentence`
* `[], greeting, introduction`
* `[hello], introduction`
* `[hello, my, name, is], name`
* `[hello, my, name, is, will]`

At each stage we replace a non-terminal with the RHS of its rule, we accumulate
the non-terminals into a list starting with the empty list. Parsers *consume*
terminals, that is given a sentence, rules will match part of the sentence.

How would we parse the `greeting` rule in prolog using difference lists? 
We represent the parsed terminals as the difference between two lists:
`greeting(L1, L2)` the difference between `L1` and `L2` should be `hello`,
we can write this as `greeting([hello|Rest], Rest)`, we match `hello` from the
head of the first list, consuming it, leaving `Rest`.

Let's see how this predicate functions in a few queries:

```prolog
?- greeting([hello], Rest).
Rest = []

?- greeting([hello, my, name, is ,will], Rest).
Rest = [my, name is will]

?- greeting(Sentence, [my, name, is will]).
Sentence = [hello, my, name, is will]

?- greeting([], [])
false.

?- greeting([hello], [])
true.

?- greeting([hello, my, name, is will], [])
false.
```

Although `greeting` was arguably the simplest of the grammar rules, the concept
applies to all other grammar rules, all we're doing is consuming terminals from
the first list, putting the resulting list in the second argument.

Let's convert the rest of the grammar rules to Prolog in difference list form.

`name` is very similar to `greeting`, we simply consume the name.

```prolog
name([will|Rest], Rest).
name([tom|Rest], Rest).
name([henry|Rest], Rest).
```

`introduction` is slightly more complicated as now we have a non-terminal in
the RHS of the rule

```prolog
introduction([my, name, is|Rest1], Rest2) :- name(Rest1, Rest2).
```

This deserves some explanation. `introduction` consumes the non-terminals on the
RHS of its corresponding grammar rule, but then we also need to give the rest of the
sentence to the `name` parser so it can check that the rest of the sentence is
a name. To do this we pass the remainder of the sentence, `Rest1`, onto `name` which
results in another list, containing the remainder of the sentence after
matching the name in `Rest2`. Let's give some pseudo-Prolog examples to further
demonstrate how this works:

```prolog
% This is not a real prolog session, I've written out the intermediate
% variables to aid the understanding of which parts of the sentence are
% consumed by which parsers

?- introduction([my, name, is, will], X).
Rest1 = [will],
Rest2 = [],
X = Rest2 = []

?- introduction([my], X).
false
% Prolog can't match the [my] to [my, name, is|Rest1] as the list is missing [name, is]

?- introduction([my, name, is, Name], []).
Name = will;
Name = tom;
Name = henry
```

Finally the sentence rule:

```prolog
sentence(L1, L3) :- greeting(L1, L2), introduction(L2, L3).
```

and some examples:

```prolog
% This is not a real prolog session, I've written out the intermediate
% variables to aid the understanding of which parts of the sentence are
% consumed by which parsers

?- sentence([hello, my, name, is will], []).
L1 = [hello, my, name, is will],
L2 = [my, name, is will],
L3 = []
true.
% greeting/2 consumes `hello` from the list leaving L2,
% which is then fully consumed by introduction/2 resulting
% in L3 = []

?- sentence(Sentence, []).
Sentence = [hello, my, name, is will];
Sentence = [hello, my, name, is tom];
Sentence = [hello, my, name, is henry].

?- sentence([my, name, is, will], [will]).
false.
% Because name is called like `name([will|Rest], [will])`, it doesn't match the
% definition of `name/2` so fails.
```

Translating these grammar rules is very mechanical, which is why Prolog
introduces syntactic sugar for them! Yay! The grammar we gave before can be
rewritten as:

```prolog
sentence --> greeting, introduction.
greeting --> [hello].
introduction --> [hello, my, name, is], name.
name --> [will].
name --> [tom].
name --> [henry].
```

We also don't have to explicitly call the  predicates like `sentence(Sentence,
[])`, we can use `phrase/2` instead: `phrase(sentence, Sentence)` is equivalent
to the previous call.


## More resources

* [Learn Prolog Now! Chapter 7: Definite Clause Grammars](http://www.learnprolognow.org/lpnpage.php?pagetype=html&pageid=lpn-htmlch7)
* [Using Definite Clause Grammars in SWI-Prolog (Anne Ogborn)](http://www.pathwayslms.com/swipltuts/dcg/)
