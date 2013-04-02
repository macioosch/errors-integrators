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
    double dt = 1e-5, x0 = 1.0, v0 = 0.0, b = 0.0;
    char *algorithmName = NULL, takeArguments[] = "abitvx";
    opterr = 0;
    while ((c = getopt(argc, argv, "a:b:i:mst:v:x:")) != -1)
        switch (c) {
        case 'a': algorithmName = optarg; break;
        case 'b': b = atof(optarg); break;
        case 'i': iterations = (int) atof(optarg); break;
        case 'm': fprintf(stdout, "# Dt; std. dev. of E; x; v for \"%s\", b = %.1e\n", algorithmName, b); return 0;
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
                "damping coefficient b:\t%e.\n"
                , algorithmName, iterations, dt, x0, v0, b);

	// end of CLI options parsing
    
	const double e0 = energy(x0, v0);
    double x = x0, v = v0, e, sumDE2 = 0.0, sumDX2 = 0.0, sumDV2 = 0.0, t = 0.0;

	// (double xi, double vi, double t, double dt, double b, double &xf, double &vf);
    void (*integrator)(double, double, double, double, double, double&, double&);

    if (strcmp(algorithmName, "Euler") == 0)
        integrator = euler;
    else if (strcmp(algorithmName, "RK4") == 0)
        integrator = rK4;
    else if (strcmp(algorithmName, "VelocityVerlet") == 0)
        integrator = verletVelocity;
    else if (strcmp(algorithmName, "Verlet") == 0)
    {
        initX(x);
        rK4(x, v, t, dt, b, x, v);
		double xa = analyticX(x0, v0, t, b);
		double va = analyticV(x0, v0, t, b);
        sumDE2 += pow(energy(x,v)-energy(xa,va), 2);
		sumDX2 += pow(x-xa, 2);
		sumDV2 += pow(v-va, 2);
        t += dt;
        integrator = verlet;
    }
    else if (strcmp(algorithmName, "VerletLeapFrog") == 0)
    {
        initV(v);
        rK4(x, v, t, dt, b, x, v);
		double xa = analyticX(x0, v0, t, b);
		double va = analyticV(x0, v0, t, b);
        sumDE2 += pow(energy(x,v)-energy(xa,va), 2);
		sumDX2 += pow(x-xa, 2);
		sumDV2 += pow(v-va, 2);
        t += dt;
        integrator = verletLeapFrog;
    }

    // computations
    for (int index=0; index < iterations; index++) {
        (*integrator)(x, v, t, dt, b, x, v);
        t += dt;
		double xa = analyticX(x0, v0, t, b);
		double va = analyticV(x0, v0, t, b);
        sumDE2 += pow(energy(x,v)-energy(xa,va), 2);
		sumDX2 += pow(x-xa, 2);
		sumDV2 += pow(v-va, 2);
    }

    double stdDevE = sqrt(sumDE2/iterations)/e0;
    double stdDevX = sqrt(sumDX2/iterations);
    double stdDevV = sqrt(sumDV2/iterations);

    // output
    fprintf(stdout, "%e;%e;%e;%e\n", dt, stdDevE, stdDevX, stdDevV);

    return 0;
}

