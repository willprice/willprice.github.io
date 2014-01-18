#!/usr/bin/env python

import unittest


def fib(n):
    if (n <= 2):
        return get_base_case(n)
    return fib(n - 1) + fib(n - 2)

def get_base_case(n):
    return n - 1


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
