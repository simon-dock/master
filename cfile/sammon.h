#ifndef COMPLETED
#define COMPLETED

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define READFILENAME "origin.txt"
#define WRITEFILENAME "data.txt"

typedef struct arrayTwo{
    double **data;
    int size;
    int dimension;
}arrayTwo;

void readFile(arrayTwo *array, arrayTwo *learn);
void writeFile(arrayTwo *array);

void makeArray(arrayTwo *array);
void input(arrayTwo *array);
void inputRandam(arrayTwo *array);
void assignment(arrayTwo *array1, arrayTwo *array2);
void printArray(arrayTwo *array);

double extreme(arrayTwo *origin, arrayTwo *learn);
void autodifferen(double *partdiff, arrayTwo *origin, arrayTwo *learn);
double differential(arrayTwo *origin, arrayTwo *learn, arrayTwo *delta);
double calError(arrayTwo *origin, arrayTwo *learn);
double calDistance(double *data1, double *data2, int dimension);

#endif