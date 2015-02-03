def selectionSort(list):
    """
    >>> selectionSort([1])
    [1]
    >>> selectionSort([2])
    [2]
    >>> selectionSort([1, 2])
    [1, 2]
    >>> selectionSort([2, 1])
    [1, 2]
    >>> selectionSort([3, 2, 1])
    [1, 2, 3]
    >>> selectionSort([14,2,1,4])
    [1, 2, 4, 14]
    """
    for targetIndex in range(0, len(list) - 1):
        indexOfmin = targetIndex

        for index in range(targetIndex, len(list)):
            if list[index] < list[indexOfmin]:
                indexOfmin = index

        swap(list, indexOfmin, targetIndex)

    return list


def swap(list, i1, i2):
        tmp = list[i1]
        list[i1] = list[i2]
        list[i2] = tmp


if __name__ == '__main__':
    import doctest
    doctest.testmod()
