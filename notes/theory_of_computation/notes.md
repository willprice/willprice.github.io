---
title: Theory of computation notes
layout: layout
---

# Context-free languages

A context-free grammar consists of a set of **substitution rules**, otherwise
known as **productions**. **Variables** map to more variables and/or
**terminals**. A word in the language consists entirely of terminals. One
variable in the grammar is chosen as the **start variable** from which all words
of the language are produced.

The general steps of deriving a word in a CFL:
1. Write down start variable **S**.
2. Find a rule that maps **S** and write down the right-hand side.
3. Goto *2* until no variable remains.

The set of strings that can be *derived* from a set of rules is called the
*language of the grammar*.

A **CFG** is defined as a 4 tuple: `$$\right(V, \Sgima, R, S \left)$$`. 
* `$$V$$` - A finite set: **variables**.
* `$$\Sigma$$` - A finite set s.t `$$\Sigma \cap V = \emptyset$$` the
  **terminals**.
* `$$R$$` - A finite set of rules, with each rule being a variable and a string
  of variables and terminals.
* `$$S$$` - The start variable s.t. `$$S \in V$$`.

## Designing CFLs
Many CFLs are the union of simpler CFLs. Merging simpler CFLs into a more
complex CFL is achieved by merging their grammars and adding a new start
variable that maps to the union of all the old start variables from the simpler
CFLs.

### DFA to CFG
For each state in the machine add a rule `$$R_i \Rightarrow aR_j$$` for every
transition from state `$$R_i$$` to state `$$R_j$$` when reading the symbol
`$$a$$`. 

## Ambiguity
Some CFGs will allow derivation of strings in a few different ways. This leads
to the idea of **ambiguity** in derivation. A grammar is ambiguous if you can
derive any string ambiguously. 

* **Leftmost derivations**  are derivations in which the **Leftmost** variable
  is always replaced.

Some languages can only be defined ambiguously, those grammars are known as
**inherently ambiguous**.

## Chomsky normal form
All CFGs can be expressed in **Chomsky normal form** where all rules are of the
form:

* `$$A \Rightarrow BC$$`
* `$$A \Rightarrow a$$`
* `$$S \Rightarrow \epsilon` is the only mapping to `$$epsilon$$` permitted in
  the grammar. (`$$S$$` is the start variable)


# Pushdown Automata
