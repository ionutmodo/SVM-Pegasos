#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "util.h"

Dataset* readDataset(const char *fileName)
{
    printf("Reading dataset '%s'\n", fileName);
    Dataset* dataset = (Dataset*) malloc(sizeof(Dataset));

    FILE *in = safeOpen(fileName, "r");

    fscanf(in, "%d %d", &dataset->m, &dataset->d);

    dataset->y = (int*) malloc(dataset->m * sizeof(double));
    dataset->x = (double**) malloc(dataset->m * sizeof(double*));

    int i, j;
    for(i = 0; i < dataset->m; ++i)
    {
        fscanf(in, "%d", &dataset->y[i]);
        dataset->x[i] = (double*) malloc(dataset->d * sizeof(double));
        for(j = 0; j < dataset->d; ++j)
            fscanf(in, "%lf", &dataset->x[i][j]);
    }

    fclose(in);
    return dataset;
}

static int min(int a, int b)
{
    return (a < b) ? a : b;
}

void printDataset(Dataset *dataset, int maxSamples)
{
    printf("m = %d, d = %d\n", dataset->m, dataset->d);
    int i, j;
    for(i = 0; i < min(maxSamples, dataset->m); ++i)
    {
        printf("y[%3d] = %+d, x = (", i, dataset->y[i]);
        for(j = 0; j < dataset->d - 1; ++j)
            printf("%.3lf, ", dataset->x[i][j]);
        printf("%.3lf)\n", dataset->x[i][j]);
    }
    printf("\n");
}

void deleteDataset(Dataset **dataset)
{
    freeArray((void*)&((*dataset)->y));
    ///free((void*) (*dataset)->y);
    ///(*dataset)->y = 0;
    int i;
    for(i = 0; i < (*dataset)->m; ++i)
    {
        freeArray((void*)&((*dataset)->x[i]));
        ///free((void*) (*dataset)->x[i]);
        ///(*dataset)->x[i] = 0;
    }
    freeArray((void*) &((*dataset)->x));
    ///free((void*) (*dataset)->x);
    ///(*dataset)->x = 0;

    freeArray((void*)(&dataset));
    ///free((void*) dataset);
    ///dataset = 0;
}