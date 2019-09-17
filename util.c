#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

FILE* safeOpen(const char *fileName, const char *mode)
{
    FILE *in = fopen(fileName, mode);
    if(in == 0)
    {
        printf("ERROR: cannot open file '%s' in '%s' mode!\n", fileName, mode);
        exit(EXIT_FAILURE);
    }
    return in;
}

void shuffleArray(int *v, int n)
{
    int i, j, k;
    for(i = 0; i < n; ++i)
    {
        do
        {
            j = mapValue(rand(), 0, RAND_MAX, 0, n - 1);
        }
        while(j == i);
        k = v[i];
        v[i] = v[j];
        v[j] = k;
    }
}

int mapValue(int x, int a, int b, int A, int B)
{
    int k = A + (B-A) * (x - a) / (b - a);
    return k;
}

void freeArray(void **p)
{
    free(*p);
    *p = 0;
}

void endProgram(char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}