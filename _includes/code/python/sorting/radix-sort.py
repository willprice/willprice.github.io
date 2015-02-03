def radixSort(array, maxNumberOfDigits):
    # note, this is inclusive of maxNumberOfDigits
    for digit in range(1, maxNumberOfDigits + 1):
        stableSort(array, digit)
