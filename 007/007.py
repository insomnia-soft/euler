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
    10001st prime
    Problem 7

    By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

    What is the 10001st prime number?
    """
    
    i = 2
    p = 0
    
    while p <= 10001:
        if isprime(i):
            p += 1
        i += 1
            
    print i
    return 0

if __name__ == '__main__':
    main()

