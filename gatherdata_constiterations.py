#!/usr/bin/env python
"""
Uses the "integrators" C program to generate an error vs time step plot for
different numerical integration algorithms.
"""
import os, sys
from math import pi

if __name__ == "__main__":
    IMAX = 1e6
    dt = 1e-1*2.0*pi
    os.system("././integrators -a \""+sys.argv[1]+"\" -b "+sys.argv[2]+" -m")
    while dt >= 1e-5:
        os.system("././integrators -s -a \""+sys.argv[1]+"\" -b "+sys.argv[2]
                +" -t "+str(dt)+" -i "+str(IMAX))
        dt /= 2.0
