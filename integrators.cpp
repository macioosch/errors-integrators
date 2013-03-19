#include <math.h>
#include "integrators.h"

static double xp, vp;

void initX(double x)
{
    xp = x;
}

void initV(double v)
{
    vp = v;
}

double a(double x, double v, double t)
{
    return -x;
}

void euler(double xi, double vi, double t, double dt, double &xf, double &vf)
{
    vf = vi + dt*a(xi, vi, t);
    xf = xi + dt*vi;
}

void rK4(double xi, double vi, double t, double dt, double &xf, double &vf)
{
    double  x1, v1, a1,
            x2, v2, a2,
            x3, v3, a3,
            x4, v4, a4;

    x1 = xi;
    v1 = vi;
    a1 = a(x1, v1, t);

    x2 = xi + 0.5*v1*dt;
    v2 = vi + 0.5*a1*dt;
    a2 = a(x2, v2, t + 0.5*dt);

    x3 = xi + 0.5*v2*dt;
    v3 = vi + 0.5*a2*dt;
    a3 = a(x3, v3, t + 0.5*dt);

    x4 = xi + v3*dt;
    v4 = vi + a3*dt;
    a4 = a(x4, v4, t + dt);

    xf = xi + (dt/6.0)*(v1 + 2*v2 + 2*v3 + v4);
    vf = vi + (dt/6.0)*(a1 + 2*a2 + 2*a3 + a4);
}

void verlet(double xi, double vi, double t, double dt, double &xf, double &vf)
{
    xf = 2*xi - xp + a(xi, vi, t)*pow(dt,2);
    vf = (xf - xp)/(2*dt);
    xp = xi;
}

void verletLeapFrog(double xi, double vi, double t, double dt, double &xf, double &vf)
{
    vp += dt*a(xi, vi, t);
    xf = xi + dt*vp;
    vf = vp;
}

void verletVelocity(double xi, double vi, double t, double dt, double &xf, double &vf)
{
    double a0 = a(xi, vi, t);
    xf = xi + vi*dt + 0.5*a0*pow(dt,2);
    vf = vi + 0.5*dt*(a0 + a(xf, vi, t+dt));
}
