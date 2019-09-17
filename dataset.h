#ifndef _DATASET_H_
#define _DATASET_H_

struct _Dataset
{
    int m, d;
    double **x;
    int *y;
};

typedef struct _Dataset Dataset;

Dataset* readDataset(const char *fileName);
void printDataset(Dataset *dataset, int maxSamples);
void deleteDataset(Dataset **dataset);

#endif // _DATASET_H_