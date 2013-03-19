#!/usr/bin/env python
"""
Uses the "integrators" C program to generate an error vs time step plot for
different numerical integration algorithms.
"""
import os, sys

if __name__ == "__main__":
    IMAX = 1e7
    dt = 1e-1
    os.system("././integrators -a \""+sys.argv[1]+"\" -m")
    while dt >= 1e-8:
        os.system("././integrators -s -a \""+sys.argv[1]
                +"\" -t "+str(dt)+" -i "+str(IMAX))
        dt /= 2.0
