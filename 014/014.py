#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

def main():
    """
    projecteuler.net
    
    Longest Collatz sequence
    Problem 14

    The following iterative sequence is defined for the set of positive integers:

    n → n/2 (n is even)
    n → 3n + 1 (n is odd)

    Using the rule above and starting with 13, we generate the following sequence:
    13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

    It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

    Which starting number, under one million, produces the longest chain?

    NOTE: Once the chain starts the terms are allowed to go above one million.
    """
    smax = 0
    for i in range(2, 1000001):
        step = 1
        n = i
        while (n != 1):
            step += 1
            if (n % 2):
                n = 3 * n + 1
            else:
                n /= 2
        if step > smax:
            print str(i) + ": " + str(step) + " steps"
            smax = step
    
    return 0

if __name__ == '__main__':
    main()

