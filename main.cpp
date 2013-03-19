#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "integrators.h"

int main(int argc, char **argv)
{
    // CLI options parsing
    bool silent = false;
    int c, iterations = 1000;
    double dt = 1e-5, x0 = 1.0, v0 = 0.0;
    char *algorithmName = NULL, takeArguments[] = "aitvx";
    opterr = 0;
    while ((c = getopt(argc, argv, "a:i:mst:v:x:")) != -1)
        switch (c) {
        case 'a': algorithmName = optarg; break;
        case 'i': iterations = (int) atof(optarg); break;
        case 'm': fprintf(stdout, "# Dt; std. dev. for \"%s\"\n", algorithmName); return 0;
        case 's': silent = true; break;
        case 't': dt = atof(optarg); break;
        case 'v': v0 = atof(optarg); break;
        case 'x': x0 = atof(optarg); break;
        case '?':
            if (strchr(takeArguments, optopt) == NULL)
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else
            if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default: abort();
        }

    for (int index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    if (!silent)
        fprintf(stdout,
                "Algorithm:\t%s,\n"
                "iterations:\t%d,\n"
                "time step:\t%e,\n"
                "initial x:\t%e,\n"
                "initial v:\t%e,\n"
                , algorithmName, iterations, dt, x0, v0);

    const double e0 = pow(x0,2) + pow(v0,2);
    double x = x0, v = v0, e, sumE2 = 0.0, t = 0.0;

    void (*integrator)(double, double, double, double, double&, double&);
    if (strcmp(algorithmName, "Euler") == 0)
        integrator = euler;
    else if (strcmp(algorithmName, "RK4") == 0)
        integrator = rK4;
    else if (strcmp(algorithmName, "VelocityVerlet") == 0)
        integrator = verletVelocity;
    else if (strcmp(algorithmName, "Verlet") == 0)
    {
        initX(x);
        rK4(x, v, t, dt, x, v);
        e = pow(x,2) + pow(v,2);
        sumE2 += pow(e-e0, 2);
        t += dt;
        integrator = verlet;
    }
    else if (strcmp(algorithmName, "VerletLeapFrog") == 0)
    {
        initV(v);
        rK4(x, v, t, dt, x, v);
        e = pow(x,2) + pow(v,2);
        sumE2 += pow(e-e0, 2);
        t += dt;
        integrator = verletLeapFrog;
    }

    // computations
    for (int index=0; index < iterations; index++) {
        (*integrator)(x, v, t, dt, x, v);
        e = pow(x,2) + pow(v,2);
        sumE2 += pow(e-e0, 2);
        t += dt;
    }
    double stdDevE = sqrt(sumE2/iterations)/e0;

    // output
    fprintf(stdout, "%e;%e\n", dt, stdDevE);

    return 0;
}

