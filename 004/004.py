#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

def palindrome(n):
    m = n
    p = 0
    while m > 0:
        mod = m % 10
        m /= 10
        p = p * 10 + mod
        
    if p == n:
        return True
    
    return False
    

def main():
    """
    Largest palindrome product
    Problem 4

    A palindromic number reads the same both ways. The largest
    palindrome made from the product of two 2-digit numbers is
    9009 = 91 × 99.

    Find the largest palindrome made from the product of two 3-digit
    numbers.
    """
    
    nmax = 0
    for i in range(100, 1000):
        for j in range(100, 1000):
            n = i * j;
            if palindrome(n) and n > nmax:
                nmax = n

    print nmax
    return 0

if __name__ == '__main__':
    main()

