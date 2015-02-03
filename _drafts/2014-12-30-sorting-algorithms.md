---
layout: post
title: "Sorting algorithms"
tags: ['maths', 'toc']
---
# What's the best we can achieve?
Here's an interesting question:

> Given an array of N elements, what is the fastest that any algorithm can sort
> the array.

Or in other words, what is the lowest time complexity for sorting an array of N
element. We need not devise an algorithm to sort in this time, but prove that
this is the lowest complexity that any algorithm can complete this task.

When sorting an array we compare elements. For any comparison-based sorting
algorithm we can visually represent the execution as a *decision tree*. A node
being a comparison between two elements `\(a\)` and `\(b\)`. The children of
such a node are the results where `\(a \lt b\)` and `\(a \geq b\)`. The
leaves of the tree represent the possible final orderings of the array, e.g. for
an input `[a,b,c]` the sorted results could be any one of `[a,b,c], [a,c,b],
[b,a,c], [b,c,a], [c,a,b], [c,b,a]` depending on the values of `a`, `b` and `c`.
From this example you should have the intuition that there are `N!` leaves in
the tree since that is the number of permutations of `\(N\)` elements. 

Now we consider the height of a binary tree, maximising the number of leaves at
height `\(h\)` means that the tree is perfectly balanced, so at height `\(h\)`
we have exactly `\(2^h\)` leaves (starting at the root with `\(h=0\)`). Since a
binary tree cannot have more leaves than `\(2^h\)` and a decision tree has
`\(N!\)` leaves, we can form the following inequality: `\(2^h \geq N!
\Rightarrow h \geq \log(N!) \Rightarrow h \geq N \log(N)\)`. To go from the root
of the node to a leaf (i.e. unsorted -> sorted) takes at least `\(N \log(N)\)`
in the best case.

# Sorting Algorithms
We start our investigation of sorting algorithms with the trivial and woefully
inefficient insertion sort!

## Insertion sort
Insertion sort acts by iterating over the input array, taking each element in
turn and placing it in the correct ordering in an output array. This can be done
with two separate arrays, or done in place on the input array. The algorithms
for both are so similar that I have omitted the separate array algorithm.

{% highlight python %}
{% include code/python/sorting/insertion-sort.py %}
{% endhighlight %}

### Time Complexity
The main loop inside of `insertionSort` runs `\(n-1\)` times where `\(n\)` is
the number of elements inside the array/list. `_insert_key_into_sorted_position`
calls `_find_and_allocate_position` that takes a variable amount of time to
complete dependent upon the array
#### Worst case (reverse ordered array)
`_find_and_allocate_position` takes `\(\text{keyIndex} - 1\)` time by shifting the
entire sorted array up one position each time to make room at the beginning for
the smaller key.

#### Best case (sorted array)
`_find_and_allocate_position` takes `\(\mathcal{O}(1)\)` time since the while
loop will terminate before it's first iteration.


Of note too is the space complexity: since the algorithm is operating in place
it uses a constant amount of space `\(\mathcal{O}(1)\)`.

## Selection sort
A nice easy algorithm where we start at the beginning of the list, and check the
rest of the list to see if there's a smaller element, if there is, then we swap
the two, and then move on to the next element repeatedly until we reach the end
of the list.
{% highlight python %}
{% include code/python/sorting/selection-sort.py %}
{% endhighlight %}

### Time Complexity
Since the inner for loop runs the same amount of times regardless of the input
array, the best and worst case complexity is the same. The first iteration will
perform `\(n - 1\)` comparisons, then the second `\(n - 2\)` and so on until the
last element that performs no comparisons. The running time will take
`\(\sum_{i = 1}^{n}(n - i) \in \mathcal{O}(n^2)\)`

## Radix sort
```python
def radixSort(array, maxNumberOfDigits):
    # note, this is inclusive of maxNumberOfDigits
    for digit in range(1, maxNumberOfDigits + 1):
        stableSort(array, digit)
```
Using a stable sorting algorithm we sort the array `\(\text{maxNumberOfDigit}\)`
times each time sort the array by one of the digits starting from the lowest to
the highest. Providing the algorithm we use to sort is stable, after the final
sorting, all the elements will be in order

### Time Complexity
Time complexity is dependent upon the stable sort you use, and it is
`\(maxNumberOfDigits\)` times that complexity (which is usually is the same,
unless you're expecting very long numbers with lots of digits.)

## Quick sort
The premise of quick sort is very simple and elegant. Partition your array into
three parts after picking an element you call the *pivot*:
* Everything less than or equal to the pivot (but not the pivot itself)
* Everything greater than the pivot
* The pivot itself

For the first two arrays we sort them recursively using the same principle,
until we're trying to sort an array of length one, which is trivially sorted!
```
def QuickSort(array):
    QuickSort(array, 0, array.length)

def QuickSort(array, startIndex, stopIndex):
    # We terminate the recursion when startIndex = stopIndex
    # as now we have an array of a single element which is thus
    # trivially sorted
    if startIndex < stopIndex:
        # Split up the array into three parts:
        # [x | x <= pivot], [pivot], [x | x > pivot]
        pivotIndex = Partition(array, startIndex, stopIndex)
        # Now we sort the lower array recursively
        QuickSort(array, startIndex, pivotIndex - 1)
        # Likewise with the upper array
        QuickSort(array, pivotIndex + 1, stopIndex)

def Parition(array, startIndex, stopIndex)
```
{% highlight python %}
{% include code/python/sorting/quick-sort.py %}
{% endhighlight %}

### Choosing a pivot
Chosing the pivot determines how efficient our algorithm is going to be, in the
worst case, where we pick the pivot as the first or last element in a sorted
array, the complexity is `\(\mathcal{O}(n^2)\)` whereas if the array is split
evenly each time the complexity is `\(mathcal{O}(n\log{n}\)`.


### Time Complexity
#### Worst case
#### Best case

## Bubble sort
{% highlight python %}
{% include code/python/sorting/bubble-sort.py %}
{% endhighlight %}
### Time Complexity
#### Worst case
#### Best case

## Counting sort
{% highlight python %}
{% include code/python/sorting/counting-sort.py %}
{% endhighlight %}
### Time Complexity
#### Worst case
#### Best case
