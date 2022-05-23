

#include <stdio.h>
#include <stdlib.h>
#include "local.h"
#include <time.h>

int main()
{
    Stack *oristack = (Stack *) malloc (sizeof(Stack));
    oristack->head = NULL;
    Stack *newstack = (Stack *) malloc (sizeof(Stack));
    newstack->head = NULL;

    int n;
    clock_t start = clock();
    readFile(oristack, &n);
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;


clock_t starta = clock();
    operate(oristack,          // asal
            newstack,          // hasil
            n-1                  // jumlah aljabar
            );
                    // -> *Stack
clock_t stopa = clock();
    double elapseda = (double)(stopa - starta) * 1000.0 / CLOCKS_PER_SEC;


clock_t startb = clock();
    writeResult(newstack,
                n-1
                );     // -> CUI
                clock_t stopb = clock();
    double elapsedb = (double)(stopb - startb) * 1000.0 / CLOCKS_PER_SEC;

    printf("\n");
    printf("Time elapsed in readFile() ms: %f\n", elapsed);
     printf("Time elapsed in operate() ms: %f\n", elapseda);
    printf("Time elapsed in writeResult() ms: %f\n", elapsedb);

}
