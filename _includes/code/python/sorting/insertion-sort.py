def insertionSort(list):
    """
    >>> insertionSort([1])
    [1]
    >>> insertionSort([2])
    [2]
    >>> insertionSort([1, 2])
    [1, 2]
    >>> insertionSort([2, 1])
    [1, 2]
    >>> insertionSort([2, 3, 1])
    [1, 2, 3]
    >>> insertionSort([14,2,1,4])
    [1, 2, 4, 14]
    """
    for index in range(1, len(list)):
        _insert_key_into_sorted_position(list, index)

    return list


def _insert_key_into_sorted_position(list, keyIndex):
        key = list[keyIndex]
        position = _find_and_allocate_position(list, keyIndex)
        list[position] = key


def _find_and_allocate_position(list, keyIndex):
        """ Shifts all the elements greater than the key up by one to make room
            for the key.

            Save the key before running this as it will overwrite it in the
            list.

            returns the index of the keys new position"""
        key = list[keyIndex]
        position = keyIndex - 1

        # searching from largest to smallest, find the first element that is
        # smaller than the key
        while position >= 0 and list[position] > key:
            # Shift the element up by one (to make room for the key)
            list[position + 1] = list[position]
            position -= 1
        # We have now either exhausted all posibilities, or found an element
        # with index = position whose value is less than or equal to the key,
        # so we return the sorted position of the key which is one more than
        # that of the previous element

        return position + 1

if __name__ == '__main__':
    import doctest
    doctest.testmod()
