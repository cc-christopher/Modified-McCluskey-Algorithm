

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 255

//  Nodus data lama
typedef struct Node {
    char data[MAX_STR];         // string penyimpan satu path
    int yes;
    struct Node* next;                 // selanjutnya
}Node;


// Stack pengakses tumpukan nodus
typedef struct Stack {
    Node* head;                     // alamat tumpukan teratas
} Stack;

// baca file dan susun stack
void readFile(
             Stack *astack,
             int *len);

// fungsi rekursif
int operate(
            Stack *orione,           // tumpukan string path
            Stack *newone,         // tumpukan string hasil
            int n);                         // jumlah variabel


// debugging
void writeResult(
                 Stack *refstack,        // stack path_list
                 int n);



