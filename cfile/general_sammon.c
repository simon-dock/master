#include"sammon.h"

/*
配列 array[size][dimension] を動的に確保し先頭アドレスを返す
メモリの解放忘れに注意 malloc関数によって引数のアドレスからアドレスが変更される
*/
void makeArray(arrayTwo *array){

    int i;

    array->data = (double**)malloc(sizeof(double*)*array->size);
    array->data[0] = (double*)malloc(sizeof(double)*array->dimension*array->size);
    if(array->data == NULL) exit(0);
    for(i=1; i<array->size; i++){
        array->data[i] = array->data[i-1] + array->dimension;
    }
}

/*
配列に値を代入
*/
void input(arrayTwo *array){
    
    int i,j;

    for(i=0;i<array->size;i++){
        for(j=0;j<array->dimension;j++){
            array->data[i][j]=i*2;
        }
    }
}

/*
配列に値をランダムに代入
*/
void inputRandam(arrayTwo *array){
    
    int i,j;

    for(i=0;i<array->size;i++){
        for(j=0;j<array->dimension;j++){
            array->data[i][j]=rand()%10;
        }
    }
}

/*
data1にdata2の値を代入
二つのdataは配列の形が全く同じ必要がある
*/
void assignment(arrayTwo *array1, arrayTwo *array2){
    
    int i,j;

    for(i=0;i<array1->size;i++){
        for(j=0;j<array1->dimension;j++){
            array1->data[i][j] = array2->data[i][j];
        }
    }
}

/*
配列の中身を表示
*/
void printArray(arrayTwo *array){
    
    int i, j;
    
    for(i=0;i<array->size;i++){
        for(j=0;j<array->dimension;j++){
            printf("%f,",array->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}