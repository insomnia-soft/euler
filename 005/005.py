#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

def main():
    """
    Smallest multiple
    Problem 5

    2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

    What is the smallest positive number that is evenly divisible (divisible with no remainder) by all of the numbers from 1 to 20?
    """
    
    dividers = 10
    i = dividers + 1
    loop = 1
    
    while (loop):
        for j in range(1, dividers + 1):
            if i % j != 0:
                break
            if j == dividers:
                loop = 0
        i += 1
    i -= 1
        
    print i    
    return 0

if __name__ == '__main__':
    main()

