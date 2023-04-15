#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define H 0.00000000001
#define STEP 0.5
#define LIMIT 100000
#define SIZE 5
#define NDIMENSION 4
#define LDIMENSION 2
#define PROGRESS false

double **makeArray(double **data, int dimension, int size);
void input(double **data, int dimension, int size);
void inputRandam(double **data, int dimension, int size);
void assignment(double **data1, double **data2, int dimension, int size);
void printArray(double **data, int dimension, int size);

double extreme(double **dataOrigin, double **dataLearn, int dimenOrigin, int dimenLearn, int size);
void autodifferen(double *partdiff, double **dataOrigin, double **dataLearn, int dimenOrigin, int dimenLearn, int size);
double differential(double **dataOrigin, double **dataLearn, double **dataDelta, int dimenOrigin, int dimenLearn, int size);
double calError(double **dataOrigin, double **dataLearn, int dimenOrigin, int dimenLearn, int size);
double calDistance(double *data1, double *data2, int dimension);


int main(void){

    int i,j;
    int size = SIZE, dimenOrigin = NDIMENSION, dimenLearn = LDIMENSION;
    double **dataOrigin, **dataLearn;
    double error;

    dataOrigin = makeArray(dataOrigin, dimenOrigin, size);
    dataLearn = makeArray(dataLearn, dimenLearn, size);

    input(dataOrigin, dimenOrigin, size);
    inputRandam(dataLearn, dimenLearn, size);

    printArray(dataOrigin, dimenOrigin, size);
    printArray(dataLearn, dimenLearn, size);

    error = extreme(dataOrigin, dataLearn, dimenOrigin, dimenLearn, size);

    printf("error : %.32f\n", error);
    printArray(dataLearn, dimenLearn, size);

    free(dataOrigin);
    free(dataLearn);
    
    return 0;
}

/*
配列 array[size][dimension] を動的に確保し先頭アドレスを返す
メモリの解放忘れに注意 malloc関数によって引数のアドレスからアドレスが変更される
*/
double **makeArray(double **data, int dimension, int size){

    int i;

    data = (double**)malloc(sizeof(double*)*size);
    data[0] = (double*)malloc(sizeof(double)*dimension*size);
    if(data == NULL) exit(0);
    for(i=1; i<size; i++){
        data[i] = data[i-1] + dimension;
    }

    return data;
}

/*
配列に値を代入
*/
void input(double **data, int dimension, int size){
    
    int i,j;

    for(i=0;i<size;i++){
        for(j=0;j<dimension;j++){
            data[i][j]=i*2;
        }
    }
}

/*
配列に値をランダムに代入
*/
void inputRandam(double **data, int dimension, int size){
    
    int i,j;

    for(i=0;i<size;i++){
        for(j=0;j<dimension;j++){
            data[i][j]=rand()%10;
        }
    }
}

/*
data1にdata2の値を代入
二つのdataは配列の形が全く同じ必要がある
*/
void assignment(double **data1, double **data2, int dimension, int size){
    
    int i,j;

    for(i=0;i<size;i++){
        for(j=0;j<dimension;j++){
            data1[i][j]=data2[i][j];
        }
    }
}

/*
配列の中身を表示
*/
void printArray(double **data, int dimension, int size){
    
    int i, j;
    
    for(i=0;i<size;i++){
        for(j=0;j<dimension;j++){
            printf("%f,",data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
最急降下法を実行し最終的なEを返す
*/
double extreme(double **dataOrigin, double **dataLearn, int dimenOrigin, int dimenLearn, int size){

    int i,j;
    int count = 0;
    double a = STEP, error = 10000;
    double *partdiff;

    partdiff = (double*)malloc(sizeof(double)*size*dimenLearn);
    if(partdiff == NULL) exit(0);

    while(count < LIMIT){
        count++;
        autodifferen(partdiff, dataOrigin, dataLearn, dimenOrigin, dimenLearn, size);
        for(i=0; i<size; i++){
            for(j=0; j<dimenLearn; j++){
                dataLearn[i][j] -= a * partdiff[i*dimenLearn+j];
            }
        }
        error = fabs(calError(dataOrigin, dataLearn, dimenOrigin, dimenLearn, size));

        if(PROGRESS == true) printf("%d:%f\n", count, error);
    }

    free(partdiff);

    return error;
}

/*
自動偏微分を実行
*/
void autodifferen(double *partdiff, double **dataOrigin, double **dataLearn, int dimenOrigin, int dimenLearn, int size){

    int i,j;
    double **dataDelta;

    dataDelta = makeArray(dataDelta, dimenLearn, size);
    assignment(dataDelta, dataLearn, dimenLearn, size);

    for(i=0; i<size; i++){
        for(j=0; j<dimenLearn; j++){
            dataDelta[i][j] = dataLearn[i][j] + H;
            partdiff[i*dimenLearn+j] = differential(dataOrigin, dataLearn, dataDelta, dimenOrigin, dimenLearn, size);
            dataDelta[i][j] = dataLearn[i][j];
        }
    }
    
    free(dataDelta);
}

/*
微分を実行し値を返す
*/
double differential(double **dataOrigin, double **dataLearn, double **dataDelta, int dimenOrigin, int dimenLearn, int size){
    
    return (calError(dataOrigin, dataDelta, dimenOrigin, dimenLearn, size) - calError(dataOrigin, dataLearn, dimenOrigin, dimenLearn, size)) / H;
}

/*
Eを計算し値を返す
*/
double calError(double **dataOrigin, double **dataLearn, int dimenOrigin, int dimenLearn, int size){
    
    int i, j;
    double dist_base, dist_modified;
    double sum_base = 0.0, sum_modified = 0.0;

    for(i=0; i<size; i++){
        for(j=i+1; j<size; j++){
            dist_base = calDistance(dataOrigin[i], dataOrigin[j], dimenOrigin);
            dist_modified = calDistance(dataLearn[i], dataLearn[j], dimenLearn);
            sum_base += dist_base;
            sum_modified += pow(dist_base-dist_modified,2.0) / dist_base;
        }
    }

    return sum_base / sum_modified;
}

/*
２点間の距離を計算し値を返す　多次元対応
*/
double calDistance(double *data1, double *data2, int dimension){

    int i;
    double difference = 0.0, sum = 0.0;

    for(i=0; i<dimension; i++){
        difference = data1[i];
        difference -= data2[i];
        sum += pow(difference,2.0);
    }

    return sqrt(sum);
}