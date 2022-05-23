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
    clock_t start_read = clock();
    readFile(oristack, &n);
    clock_t stop_read = clock();
    double elapsed_read = (double)(stop_read - start_read) * 1000.0 / CLOCKS_PER_SEC;

    clock_t start_op = clock();
    operate(oristack,          // source stack
            newstack,          // results stack
            n-1                // num. of variables
            );
                    // -> *Stack
    clock_t stop_op = clock();
    double elapsed_op = (double)(stop_op - start_op) * 1000.0 / CLOCKS_PER_SEC;

    clock_t start_write = clock();
    writeResult(newstack,
                n-1
                );     // -> CUI
    clock_t stop_write = clock();
    double elapsed_write = (double)(stop_write - start_write) * 1000.0 / CLOCKS_PER_SEC;

    printf("\nTime elapsed in readFile(): %f ms\n", elapsed_read);
    printf("Time elapsed in operate(): %f ms\n", elapsed_op);
    printf("Time elapsed in writeResult(): %f ms\n", elapsed_write);
}
