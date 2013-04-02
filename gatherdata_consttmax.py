#!/usr/bin/env python
"""
Uses the "integrators" C program to generate an error vs time step plot for
different numerical integration algorithms.
"""
import datetime, os, sys
from math import pi

if __name__ == "__main__":
    TMAX = 10.0*2.0*pi
    dt = 1e-1*2.0*pi
    elapsedTime = 0.0
    os.system("././integrators -a \""+sys.argv[1]+"\" -b "+sys.argv[2]+" -m")
    while elapsedTime < 2.0:
        beginTime = datetime.datetime.now()
        os.system("././integrators -s -a \""+sys.argv[1]+"\" -b "+sys.argv[2]
                +" -t "+str(dt)+" -i "+str(TMAX/dt))
        elapsedTime = (datetime.datetime.now() - beginTime).total_seconds()
        dt /= 2.0
