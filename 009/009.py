#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

def main():
    """
    Special Pythagorean triplet
    Problem 9

    A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
    a^2 + b^2 = c^2

    For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

    There exists exactly one Pythagorean triplet for which a + b + c = 1000.
    Find the product abc.
    """
    
    for i in range(1, 1000):
        for j in range(1, 1000):
            k = 1000 - i - j
            if i != j and i != k and i**2 + j**2 == k**2:
                print "a = " + str(i) + "  b = " + str(j) + "  c = " + str(k) + "  product = " + str(i * j * k)
    
    return 0

if __name__ == '__main__':
    main()

