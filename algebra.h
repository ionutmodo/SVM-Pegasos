#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

double dotProduct(double *x, double *y, int n);
void scaleVector(double *x, int n, double scalar);
void sumVectors(double *x, double *y, int n, double *s);
double norm(double *x, int n);

#endif // _ALGEBRA_H_