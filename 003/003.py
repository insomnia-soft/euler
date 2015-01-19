#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

def prime(n):
    loop = 1
    i = 2    
    while (loop):
        if (n % i == 0):
            return False            
        if (n / i < 2):
            loop = 0            
        i += 1
    return True

def main():
    """
    Largest prime factor
    Problem 3

    The prime factors of 13195 are 5, 7, 13 and 29.

    What is the largest prime factor of the number 600851475143 ?
    """

    n = 600851475143
    prim = 2
    loop = 1
    maxPrim = 0
    while (True):
        if (n % prim == 0):
            n /= prim
            maxPrim = prim
        else:
            while (loop):
                prim += 1
                if prime(prim):
                    break
                    
        if (n == 1):
            break
            
    print maxPrim
    return 0

if __name__ == '__main__':
    main()

