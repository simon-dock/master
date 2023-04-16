#ifndef COMPLETED
#define COMPLETED

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

//main,algorithmに分割宣言している　defineの中身を変更し、remakeしても実行ファイルに更新されなかったから
#define READFILENAME "origin.txt"
#define WRITEFILENAME "data.txt"

//二次元配列array[size][dimension]を動的かつ関数で使い易くするための構造体
typedef struct arrayTwo{
    double **data;
    int size;
    int dimension;
}arrayTwo;

//file
void readFile(arrayTwo *array, arrayTwo *learn);
void writeFile(arrayTwo *array);

//general
void makeArray(arrayTwo *array);
void input(arrayTwo *array);
void inputRandam(arrayTwo *array);
void assignment(arrayTwo *array1, arrayTwo *array2);
void printArray(arrayTwo *array);

//algorithm
double extreme(arrayTwo *origin, arrayTwo *learn);
void autodifferen(double *partdiff, arrayTwo *origin, arrayTwo *learn);
double differential(arrayTwo *origin, arrayTwo *learn, arrayTwo *delta);
double calError(arrayTwo *origin, arrayTwo *learn);
double calDistance(double *data1, double *data2, int dimension);

#endif