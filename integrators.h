#ifndef INTEGRATORS_H
#define INTEGRATORS_H

void initX(double x);
void initV(double v);
void euler(double xi, double vi, double t, double dt, double b, double &xf, double &vf);
void rK4(double xi, double vi, double t, double dt, double b, double &xf, double &vf);
void verlet(double xi, double vi, double t, double dt, double b, double &xf, double &vf);
void verletLeapFrog(double xi, double vi, double t, double dt, double b, double &xf, double &vf);
void verletVelocity(double xi, double vi, double t, double dt, double b, double &xf, double &vf);
double analyticX(double xi, double vi, double t, double b);
double analyticV(double xi, double vi, double t, double b);
double energy(double x, double v);

#endif // INTEGRATORS_H
