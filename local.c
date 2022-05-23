# include "local.h"

void readFile(
              Stack * astack,
              int *len
              )
{
    char filename[MAX_STR], buffer[MAX_STR];
	int i = 0;

    //enter file name
    printf("Please enter filename with extension: ");
    scanf("%s", filename);
	FILE *fp = fopen(filename, "r");

    //not found
    if (fp == NULL){
        printf("\nError: file invalid!\n");
        fclose(fp);
        exit(1);
    }

    //obtain first line
    fgets (buffer, MAX_STR, fp);

    //exits when the line is empty
    if(buffer == NULL){
        printf("\nError: file empty!\n");
        fclose(fp);
        exit(1);
    }

    // assign length of minterm string as number of var.
    *len = strlen(buffer);

    // create new minterm node
    Node * newNode = (Node *) malloc((sizeof(Node)));
    strcpy(newNode->data, buffer);
    newNode->yes = 0;

    newNode->next = astack->head;
    astack->head = newNode;

    //do it until the end line
    while(fgets (buffer, MAX_STR, fp) != NULL){
        Node * newNode = (Node *) malloc((sizeof(Node)));
        strcpy(newNode->data, buffer);
        newNode->yes = 0;

        newNode->next = astack->head;
        astack->head = newNode;
    }
    fclose(fp);
}

int operate(
            Stack *orione,
            Stack *newone,
            int n
            )
{
    // handshake all nodes in the stack
    Node * currNode = orione->head;
    while (currNode->next != NULL) {
        Node * secNode = currNode->next;
        while (secNode != NULL) {

            char oristr[n];
            strcpy(oristr, currNode->data);
            char secStr[n];
            strcpy(secStr, secNode->data);

            // simpilfy IF between two minterms *oristr* and *secStr* have only one difference
            int difbool = 0;
            for (int i=0; i<n; i++) {
                if (oristr[i] != secStr[i]) {
                    difbool++;
                }
            }
            if (difbool == 1) {
                currNode->yes = 1;
                secNode->yes = 1;

                char newstr[n];
                strcpy(newstr, oristr);
                // set the different variable as -
                for (int i=0; i<n; i++) {
                    if (newstr[i] != secStr[i]) {
                        newstr[i] = '-';
                    }
                }
                // write this new minterm to a new stack
                Node * newNode = (Node *) malloc((sizeof(Node)));
                strcpy(newNode->data, newstr);
                newNode->yes = 0;
                newNode->next = newone->head;
                newone->head = newNode;
            }
            secNode = secNode->next;
        }
        currNode = currNode->next;
    }

    Node * checkNode = orione->head;
    // if all nodes inside origin stack cannot be simplified, assign recuse to FALSE
    int recurse = 0;
    while(checkNode != NULL) {
        if (checkNode->yes == 0) {
            Node * newNode = (Node *) malloc((sizeof(Node)));
            strcpy(newNode->data, checkNode->data);
            newNode->yes = 0;
            newNode->next = newone->head;
            newone->head = newNode;
        }
        else {
            recurse = 1;
        }
        checkNode = checkNode->next;
    }
    Stack *emptystack = (Stack *) malloc (sizeof(Stack));
    emptystack->head = NULL;

    if (recurse) {
        // recurse the new stack as origin, set an empty stack too
        operate(newone, emptystack, n);
    }
}

void writeResult(
                 Stack *refstack,
                 int n
                 )
{
    printf("\n");
    Node * currNode = refstack->head;
    // print first variable as A -> B -> ... -> Z -> a -> b -> ... -> z
    // if NOT use '
    for (int i=0; i<n; i++) {
        if (currNode->data[i] == '1') {
            printf("%c", i+65);
        }
        else if (currNode->data[i] == '0') {
            printf("%c'", i+65);
        }
    }
    currNode = currNode->next;
    while (currNode != NULL) {
        printf(" + ");
        for (int i=0; i<n; i++) {
            if (currNode->data[i] == '1') {
                printf("%c", i+65);
            }
            else if (currNode->data[i] == '0') {
                printf("%c'", i+65);
            }
        }
        currNode = currNode->next;
    }
    printf("\n");
}
