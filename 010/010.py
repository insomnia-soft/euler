#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

def isprime(n, primes):
    for i in primes:
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
    
    primes = [2]
    psum = 0
    
    for i in range(3, 2000000):
        if i % 10000 == 0:
            print i
        if isprime(i, primes):
            primes.append(i)
            psum += i

if __name__ == '__main__':
    main()

