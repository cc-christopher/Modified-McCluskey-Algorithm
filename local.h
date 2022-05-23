#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 255

//  minterm node
typedef struct Node {
    char data[MAX_STR];                 // minterm in binary
    int yes;                            // simplified
    struct Node* next;                  // next
}Node;

// stack
typedef struct Stack {
    Node* head;                         // pointer to the head
} Stack;

// read minterm file and fill the minterms to a stack
void readFile(
             Stack *astack,
             int *len);

// recursive function to simplify minterms
int operate(
            Stack *orione,              // origin stack
            Stack *newone,              // result stack
            int n);                     // num. of var.


// write simplification result
void writeResult(
                 Stack *refstack,       // reference stack
                 int n);                // num. of. var.



