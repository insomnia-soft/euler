#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
paths = 0

def main():
    """
    projecteuler.net
    
    Lattice paths
    Problem 15

    Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

    How many such routes are there through a 20×20 grid?
    """
    global paths
    find(0, 0, 20, 20)
    print paths
    
    return 0

def find(x, y, mx, my):
    global paths
    
    if (x == mx and y == my):
        paths += 1
    else:
        if (x < mx):
            find(x + 1, y, mx, my)
        if (y < my):
            find(x, y + 1, mx, my)

if __name__ == '__main__':
    main()

