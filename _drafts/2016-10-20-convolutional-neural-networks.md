---
layout: post
title: "Convolutional neural networks"
tags:
 - cnns
 - neural networks
---

# Preamble
It's the third year of my undergraduate degree in Computer Science at
the University of Bristol and I've had to pick a final project. The
wonderful [Dima Damen](https://www.cs.bris.ac.uk/~damen/) has agreed to
supervise me in a project investigating techniques to understand the
features learnt by convolutional neural networks (CNNs).

Machine learning at an abstract takes a standard form, in which there
are three parts, and three tasks. The parts:
* A *task*: a problem to be solved (e.g. classifying objects from images)
* A *model*: some black box that takes the input of the task transforming
  it into the expected output (e.g. a computer program that reads in
  image and spits out the object shown in the image)
* A *learning algorithm*: A way to take the *model* and an example
  dataset and tweak knobs (parameters) on the model so that given an
  input from the example dataset, it will produce the same output as the
  example is labelled with (e.g. K nearest-neighbours)

# Introduction to CNNs

Neural networks are a *model* to solve a *task*.
