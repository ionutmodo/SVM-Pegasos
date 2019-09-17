#include <stdio.h>
#include <stdlib.h>
#include <string.h> /// for memcpy
#include "algebra.h"
#include "hyperplane.h"
#include "pegasos.h"
#include "util.h"

Hyperplane* train(Dataset *dataset, int epochs, double lambda)
{
    int i, epc, step = 1, *indices, *pred;
    double eta, y, *x, *xbuf, acc;

    indices = (int*) malloc(dataset->m * sizeof(int));
    for(i = 0; i < dataset->m; ++i)
        indices[i] = i;

    const int SIZE = dataset->d * sizeof(double);

    xbuf = (double*) malloc(SIZE);
    Hyperplane *H = allocHyperplane(dataset->d);

    for(epc = 1; epc <= epochs; ++epc)
    {
        shuffleArray(indices, dataset->m);
        for(i = 0; i < dataset->m; ++i)
        {
            eta = 1.0 / (lambda * step++);
            x = dataset->x[indices[i]];
            y = dataset->y[indices[i]];

            scaleVector(H->w, dataset->d, 1.0 - eta * lambda); /// w = (1 - eta * lambda) w
            H->b = (1.0 - eta * lambda) * (H->b);
            if(y * dotProduct(x, H->w, dataset->d) < 1)
            {
                H->b += eta * y;
                memcpy(xbuf, x, SIZE); /// xbuf = x
                scaleVector(xbuf, dataset->d, eta * y); /// xbuf = eta * y * x
                sumVectors(H->w, xbuf, dataset->d, H->w); /// w = w + xbuf = (1 - eta * lambda) w + eta * y * x
            }
        }
        pred = predict(H, dataset);
        acc = accuracy(pred, dataset->y, dataset->m);
        printf("Epoch %3d - train accuracy = %.2lf\n", epc, acc * 100.0);
        free((void*) pred);
        pred = 0;
    }
    free((void*) indices);
    free((void*) xbuf);
    return H;
}

int* predict(Hyperplane *H, Dataset *dataset)
{
    double dot;
    int i, *pred = (int*) malloc(dataset->m * sizeof(int));
    for(i = 0; i < dataset->m; ++i)
    {
        dot = H->b + dotProduct(H->w, dataset->x[i], dataset->d);
        pred[i] = (dot < 0) ? -1 : 1;
    }
    return pred;
}

double accuracy(int *pred, int *truth, int n)
{
    int i, acc = 0;
    for(i = 0; i < n; ++i)
        if(pred[i] == truth[i])
            ++acc;
    return (double) acc / (double) n;
}