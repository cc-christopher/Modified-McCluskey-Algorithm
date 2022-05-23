# include "local.h"

void readFile(
              Stack * astack,
              int *len
              )
{
    char filename[MAX_STR], buffer[MAX_STR], *token;
	int i = 0;

    //input nama file dan membukanya
    printf("Masukkan sumber file: ");
    scanf("%s", filename);
	FILE *fp = fopen(filename, "r");

    //beri output error jika file tidak ditemukan (filename: "file_tidak_ada.txt")
    if (fp == NULL){
        printf("\nError: file invalid!\n");
        fclose(fp);
        exit(1);
    }

    //mengambil dimensi matriks
    fgets (buffer, MAX_STR, fp);

    //beri output error jika file kosong (filename: "file_kosong.txt")
    if(buffer == NULL){
        printf("\nError: file empty!\n");
        fclose(fp);
        exit(1);
    }

    *len = strlen(buffer);
    Node * newNode = (Node *) malloc((sizeof(Node)));
    strcpy(newNode->data, buffer);
    newNode->yes = 0;

    newNode->next = astack->head;
    astack->head = newNode;

    //mengambil data pada file .txt dan menyimpannya pada Stack
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
            Stack *orione,       // koleksi path
            Stack *newone,      // koleksi baru
            int n)
{
    Node * currNode = orione->head;
    while (currNode->next != NULL) {
        Node * secNode = currNode->next;
        while (secNode != NULL) {

            char oristr[n];
            strcpy(oristr, currNode->data);
            char secStr[n];
            strcpy(secStr, secNode->data);

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
                for (int i=0; i<n; i++) {
                    if (newstr[i] != secStr[i]) {
                        newstr[i] = '-';
                    }
                }
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
        operate(newone, emptystack, n);
    }

}
void writeResult(Stack *refstack, int n)
{
    printf("\n");
    Node * currNode = refstack->head;
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
