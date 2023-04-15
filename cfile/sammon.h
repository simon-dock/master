#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define H 0.00000000001
#define STEP 0.5
#define LIMIT 10000
#define SIZE 5
#define NDIMENSION 4
#define LDIMENSION 2
#define PROGRESS false

typedef struct arrayTwo{
    double **data;
    int size;
    int dimension;
}arrayTwo;

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