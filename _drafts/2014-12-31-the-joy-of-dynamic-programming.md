---
layout: post
title: "The joy of dynamic programming"
---

Dynamic programming, what the hell is it? In essence "it's recursion without the
repetition"[1]. 

The general formula for producing a dynamic programming algorithm from a
recursive one is to store intermediate results, and then derive an iterative
algorithm by solving the subproblems in an optimal (or near optimal) order.

Let's take a look at a simple recursive algorithm, and turn it into an algorithm
leveraging dynamic programming by a process called *memoization* (it's simply
*memorising*, talk about a £2 word for a 2 pence idea)

```python
def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)
```

Simple, but massively inefficient (`\(\mathcal{O}(\text{exp})\)1)`), rather than
recomputing the same recursive calls over and over again, why don't we store
them instead? This technique of storing results which shall be accessed later is
known as *memoization*, `fib(n - 1)` and `fib(n - 2)` both have a dependency on
`fib(n - 3)`, so why not just calculate that once, rather than twice, and so on,
this massively reduces the size of the tree of computation.

```python
fibResults = dict()


def fib(n):
    """
    >>> fib(0)
    0
    >>> fib(1)
    1
    >>> fib(2)
    1
    >>> fib(3)
    2
    >>> fib(4)
    3
    >>> fib(5)
    5
    >>> fib(6)
    8
    >>> fib(7)
    13
    >>> fib(50)
    12586269025
    """
    if n <= 1:
        return n
    try:
        a = fibResults[n - 1]
    except KeyError:
        a = fib(n - 1)
        fibResults[n - 1] = a

    try:
        b = fibResults[n - 2]
    except KeyError:
        b = fib(n - 2)
        fibResults[n - 2] = b

    return a + b


if __name__ == '__main__':
    import doctest
    doctest.testmod()
```

The doctests for this bit of code run instantly, try calculating the fiftieth
Fibonacci number with the original non memoized version!

Now you might be thinking, hang on, this is pretty easy, so easy in fact that a
computer should be able to do it, and spot on, you're right, in python 3 we have
the `lru_cache` decorator from `functools` that will take a function, and return
one where all calls are memoized, we could use it with the original program like
so:

```python
import functools


@functools.lru_cache()
def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)
```

Now this isn't quite dynamic programming as we have one last step to perform,
converting this into an iterative algorithm that computes the subproblems in a
sensible order.

    

[1] Data structures and Algorithms lectures -- Ben Sachs (University of Bristol)
