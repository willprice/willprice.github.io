---
title: "Lisp: ConsCells"
layout: layout
---

ConsCells are the building blocks of Lisp, everything in Lisp is either
a ConsCell or an Atom (strings, numbers, symbols etc). ConsCells take
the form: (CAR CDR) where CAR is another ConsCell or an atom, CDR is
always another ConsCell or the atom NIL, in which case, you've reached
the end of the list.

In Lisp, (cons 1 2) evaluates to (1 . 2), in this case, CAR=1, CDR=2

In Lisp, all lists (so all programs) are represented as ConsCells, it's
just that (a b c) == (a . (b . (c . NIL))). In this format Lisp programs
take the form of a binary tree with each ConsCell being a node.

Lisp source code is parsed into lists built out of cons cells which are
then operated on by Lisp macros
