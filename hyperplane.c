#include <stdio.h>
#include <stdlib.h>
#include "hyperplane.h"
#include "util.h"

Hyperplane* allocHyperplane(int d)
{
    Hyperplane *H = (Hyperplane*) malloc(sizeof(Hyperplane));
    H->d = d;
    H->b = 0;
    H->w = (double*) malloc(d * sizeof(double));
    int i;
    for(i = 0; i < d; ++i)
        H->w[i] = 0;
    return H;
}

void printHyperplane(Hyperplane *H)
{
    int i;
    printf("%lf x%d ", H->w[0], 0);
    for(i = 1; i < (H->d - 1); ++i)
    {
        if(H->w[i] > 0)
            printf("+ %lf x%d ", H->w[i], i);
        else
            printf("- %lf x%d ", -H->w[i], i);
    }
    if(H->w[i] > 0)
        printf("+ %lf x%d ", H->w[i], i);
    else
        printf("- %lf x%d ", -H->w[i], i);

    if(H->b > 0.0)
        printf("+");
    else
        printf("-");

    printf(" %lf = 0\n", H->b);

    if(H->d == 2)
    { /// y = mx + n
        double m = -H->w[0] / H->w[1];
        double n = -H->b / H->w[1];
        printf("y = %lf x %c %lf\n", m, (n < 0) ? '-' : '+', (n < 0) ? -n : n);
    }
}

void dumpHyperplane(Hyperplane *H, char *fileName)
{
    FILE *out = safeOpen(fileName, "w");

    fprintf(out, "%d\n%lf\n", H->d, H->b);

    int i;
    for(i = 0; i < H->d; ++i)
        fprintf(out, "%lf\n", H->w[i]);

    fclose(out);
}

Hyperplane* loadHyperplane(char *fileName)
{
    Hyperplane *H = (Hyperplane*) malloc(sizeof(Hyperplane));

    FILE *in = safeOpen(fileName, "r");

    fscanf(in, "%d", &H->d);
    fscanf(in, "%lf", &H->b);

    int i;
    for(i = 0; i < H->d; ++i)
        fscanf(in, "%lf", &H->w[i]);

    fclose(in);
    return H;
}

void deleteHyperplane(Hyperplane **H)
{
    free((void*)(*H)->w);
    (*H)->w = 0;

    free((void*) *H);
    *H = 0;
}
