#include"sammon.h"

#define SIZE 30
#define NDIMENSION 8
#define LDIMENSION 2

int main(void){

    int i,j;
    double error;
    arrayTwo origin = {NULL, SIZE, NDIMENSION};
    arrayTwo learn = {NULL, SIZE, LDIMENSION};

    readFile(&origin, &learn);
    //makeArray(&origin);
    //input(&origin);

    makeArray(&learn);
    inputRandam(&learn);
  
    printArray(&origin);
    printArray(&learn);

    error = extreme(&origin, &learn);

    printf("error : %.32f\n", error);
    printArray(&learn);

    writeFile(&learn);

    free(origin.data);
    free(learn.data);
    
    return 0;
}