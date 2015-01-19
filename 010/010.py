#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

def isprime(n):
    for i in range(2, n / 2 + 1):
        if n % i == 0:
            return False
            
    return True

def main():
    """
    Summation of primes
    Problem 10

    The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

    Find the sum of all the primes below two million.
    """
    
    psum = 0
    
    for i in range(2, 2000000):
        if i % 10000 == 0:
            print i
        if isprime(i):
            psum += i
            
    print psum
    return 0

if __name__ == '__main__':
    main()

