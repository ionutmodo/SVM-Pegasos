#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

char printMenuMain()
{
    char op;
    do {
        printf("%s\n", CLEAR_COMMAND);
        system(CLEAR_COMMAND);
        printf("Please select one option:\n");
        printf("\t1. Training new model using local dataset\n");
        printf("\t2. Predict using a previously trained model\n\n");
        printf("Answer (1-2): ");
        scanf("%c", &op);
    } while( op < '1' || op > '2');
    return op;
}

