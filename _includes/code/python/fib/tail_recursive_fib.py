#!/usr/bin/env python

import unittest


def fib(n):
    return fib_accumulator(n, 1, 0)

def fib_accumulator(counter, nth_fib, nth_minus_one_fib):
    if (counter == 1):
        return nth_minus_one_fib
    if (counter == 2):
        return nth_fib

    next_fib = nth_fib + nth_minus_one_fib
    return fib_accumulator(counter - 1, next_fib, nth_fib)


class FibonacciTests(unittest.TestCase):
    def test_first_fib_number_is_zero(self):
        self.assertEqual(0, fib(1))

    def test_second_fib_number_is_one(self):
        self.assertEqual(1, fib(2))

    def test_third_fib_number_is_one(self):
        self.assertEqual(1, fib(3))

    def test_fourth_fib_number_is_two(self):
        self.assertEqual(2, fib(4))

    def test_sixth_fib_number_is_five(self):
        self.assertEqual(5, fib(6))

if __name__ == '__main__':
    unittest.main()
