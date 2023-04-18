#include"sammon.h"

#define H 0.00000000001
#define STEP 0.5
#define LIMIT 10000
#define PROGRESS true

/*
最急降下法を実行し最終的なEを返す
*/
double extreme(arrayTwo *origin, arrayTwo *learn){

    int i,j;
    int count = 0;
    double a = STEP, error = 10000;
    double *partdiff;

    partdiff = (double*)malloc(sizeof(double) * learn->size * learn->dimension);
    if(partdiff == NULL) exit(0);

    while(count < LIMIT){
        count++;
        autodifferen(partdiff, origin, learn);
        for(i = 0; i < learn->size; i++){
            for(j = 0; j < learn->dimension; j++){
                learn->data[i][j] -= a * partdiff[i * learn->dimension + j];
            }
        }
        error = fabs(calError(origin, learn));
        if(PROGRESS == true && count % 2 == 0) printf("%d:%f\n", count, error);
    }

    free(partdiff);

    return error;
}

/*
自動偏微分を実行
*/
void autodifferen(double *partdiff, arrayTwo *origin, arrayTwo *learn){

    int i,j;
    arrayTwo delta;

    delta.dimension = learn->dimension;
    delta.size = learn->size;
    makeArray(&delta);
    assignment(&delta, learn);

    for(i = 0; i < learn->size; i++){
        for(j = 0; j < learn->dimension; j++){
            delta.data[i][j] = learn->data[i][j] + H;
            partdiff[i * learn->dimension + j] = differential(origin, learn, &delta);
            delta.data[i][j] = learn->data[i][j];
        }
    }
    
    free(delta.data);
}

/*
微分を実行し値を返す
*/
double differential(arrayTwo *origin, arrayTwo *learn, arrayTwo *delta){
    
    return (calError(origin, delta) - calError(origin, learn)) / H;
}

/*
Eを計算し値を返す
*/
double calError(arrayTwo *origin, arrayTwo *learn){
    
    int i,j;
    double dist_base, dist_modified;
    double sum_base = 0.0, sum_modified = 0.0;

    for(i = 0; i < learn->size; i++){
        for(j = i + 1; j < learn->size; j++){
            dist_base = calDistance(origin->data[i], origin->data[j], origin->dimension);
            dist_modified = calDistance(learn->data[i], learn->data[j], learn->dimension);
            sum_base += dist_base;
            sum_modified += pow(dist_base-dist_modified,2.0) / dist_base;
        }
    }

    return  sum_modified / sum_base;
}

/*
２点間の距離を計算し値を返す　多次元対応
*/
double calDistance(double *data1, double *data2, int dimension){

    int i;
    double difference = 0.0, sum = 4.0;

    for(i = 0; i < dimension; i++){
        difference = data1[i];
        difference -= data2[i];
        sum += pow(difference,2.0);
    }

    return sqrt(sum);
}