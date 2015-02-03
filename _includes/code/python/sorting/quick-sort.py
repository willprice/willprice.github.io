## WARNING BROKEN ##
def quicksort(list):
    """
    >>> quicksort([1])
    [1]
    >>> quicksort([2])
    [2]
    >>> quicksort([1, 2])
    [1, 2]
    >>> quicksort([2, 1])
    [1, 2]
    >>> quicksort([3, 2, 1])
    [1, 2, 3]
    >>> quicksort([14,2,1,4])
    [1, 2, 4, 14]
    """
    return _quicksort(list, 0, len(list))


def _quicksort(list, start, end):
    pivotIndex = partition(list, start, end)
    if start < end:
        quicksort(list, start, pivotIndex)
        quicksort(list, pivotIndex + 1, end)
    return list


def partition(list, startIndex, endIndex):
    """
    >>> partition([1,2], 0, 2)
    1
    """
    pivot = list[endIndex]
    i = startIndex
    for j in range(startIndex, endIndex):
        if (list[j] < pivot):
            swap(list, i, j)
            i += 1
    swap(list, i, endIndex)
    return i


def swap(list, i1, i2):
    tmp = list[i1]
    list[i1] = list[i2]
    list[i2] = tmp


if __name__ == '__main__':
    import doctest
    doctest.testmod()
