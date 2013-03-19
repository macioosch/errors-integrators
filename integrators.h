#ifndef INTEGRATORS_H
#define INTEGRATORS_H

void initX(double x);
void initV(double v);
void euler(double xi, double vi, double t, double dt, double &xf, double &vf);
void rK4(double xi, double vi, double t, double dt, double &xf, double &vf);
void verlet(double xi, double vi, double t, double dt, double &xf, double &vf);
void verletLeapFrog(double xi, double vi, double t, double dt, double &xf, double &vf);
void verletVelocity(double xi, double vi, double t, double dt, double &xf, double &vf);

#endif // INTEGRATORS_H
