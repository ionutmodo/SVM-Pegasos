#ifndef _PEGASOS_H_
#define _PEGASOS_H_

#include "dataset.h"
#include "hyperplane.h"

Hyperplane* train(Dataset *dataset, int epochs, double lambda);
int* predict(Hyperplane *H, Dataset *dataset);
double accuracy(int *pred, int* truth, int n);

#endif // _PEGASOS_H_