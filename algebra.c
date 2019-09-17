#include <math.h>
#include "algebra.h"

double dotProduct(double *x, double *y, int n)
{
    double s = 0.0;
    int i;
    for(i = 0; i < n; ++i)
        s = s + x[i] * y[i];
    return s;
}

void scaleVector(double *x, int n, double scalar)
{
    int i;
    for(i = 0; i < n; ++i)
        x[i] = x[i] * scalar;
}

void sumVectors(double *x, double *y, int n, double *s)
{
    int i;
    for(i = 0; i < n; ++i)
        s[i] = x[i] + y[i];
}

double norm(double *x, int n)
{
    double s = 0.0;
    int i;
    for(i = 0; i < n; ++i)
        s = s + x[i] * x[i];
    return sqrt(s);
}