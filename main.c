#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dataset.h"
#include "pegasos.h"
#include "hyperplane.h"
#include "menu.h"
#include "util.h"

/*
    Download MNIST dataset from the following link:
        https://1drv.ms/f/s!AkSjjF0je4RevlZ1T4EAmgQOY5-b
*/

int main()
{
    srand((unsigned int) time(0));

    char op, fileTrain[128], fileTest[128], fileParams[128];
    int epochs, i, *trainPred, *testPred;
    double lambda, trainAccuracy, testAccuracy;
    Dataset *trainData = NULL, *testData = NULL;
    Hyperplane *H;

    printf("Train file path: ");
    gets(fileTrain);
    if(strlen(fileTrain) == 0)
        endProgram("ERROR: invalid train file path!\n");

    printf("Test file path: ");
    gets(fileTest);

    /// don't stop program when test file is not provide
    ///if(strlen(fileTest) == 0)
        ///endProgram("ERROR: invalid test file path!\n");

    printf("Parameters file path: ");
    gets(fileParams);
    if(strlen(fileParams) == 0)
        endProgram("ERROR: invalid params file path!\n");

    printf("Epochs = ");
    scanf("%d", &epochs);

    printf("Lambda = ");
    scanf("%lf", &lambda);

    printf("\n\nTraining SVM algorithm optimized with Pegasos\n\n");

    trainData = readDataset(fileTrain); /// "mnist_train.txt"

    /// ONE - VS - REST
    /// select the positive class and the rest are negatives
    int predictedClass = 1;
    for(i = 0; i < trainData->m; ++i)
        if(trainData->y[i] != predictedClass)
            trainData->y[i] = -1;
        else
            trainData->y[i] = 1;

    ///printDataset(trainData, 20); /// maxSamples = 20

    /// measure training time
    clock_t begin = clock();
    H = train(trainData, epochs, lambda);
    clock_t end = clock();
    double totalSeconds= (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Training took %lf seconds\n", totalSeconds);

    /// printHyperplane(H);

    trainPred = predict(H, trainData);
    trainAccuracy = accuracy(trainPred, trainData->y, trainData->m);
    printf("Train accuracy: %lf\n", trainAccuracy);
    deleteDataset(&trainData);

    if(strlen(fileTest) > 0)
    {
        testData = readDataset(fileTest); /// "mnist_test.txt"
        ///if(predictedClass != -1)
        for(i = 0; i < testData->m; ++i)
            if(testData->y[i] != predictedClass)
                testData->y[i] = -1;
            else
                testData->y[i] = 1;

        testPred = predict(H, testData);
        testAccuracy = accuracy(testPred, testData->y, testData->m);
        printf("Test accuracy: %lf\n", testAccuracy);
        deleteDataset(&testData);
    }
    dumpHyperplane(H, fileParams);
    deleteHyperplane(&H);
    return 0;
}
