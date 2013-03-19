#!/usr/bin/env python
"""
Uses the "integrators" C program to generate an error vs time step plot for
different numerical integration algorithms.
"""
import datetime, os, sys

if __name__ == "__main__":
    TMAX = 10.0
    dt = 1e-1
    elapsedTime = 0.0
    os.system("././integrators -a \""+sys.argv[1]+"\" -m")
    while elapsedTime < 1.0:
        beginTime = datetime.datetime.now()
        os.system("././integrators -s -a \""+sys.argv[1]
                +"\" -t "+str(dt)+" -i "+str(TMAX/dt))
        elapsedTime = (datetime.datetime.now() - beginTime).total_seconds()
        dt /= 2.0
