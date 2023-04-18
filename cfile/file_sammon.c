#include"sammon.h"

/*
テキストファイルを読み込む
*/
void readFile(arrayTwo *array, arrayTwo *learn){

    FILE *fp;
    int count = 0;
    int index = 0;
    char str[256];
    

    fp = fopen(READFILENAME, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) return ;

    while(fgets(str, 256, fp) != NULL) {
        if(count == 0){
            array->dimension = atoi(str);
        }else if(count == 1){
            array->size = atoi(str);
            learn->size = atoi(str);
            makeArray(array);
        }else{
            array->data[index / array->dimension][index % array->dimension] = atof(str);
            index++;
        }
        count++;
	}
    printf("\n");
 
	fclose(fp); // ファイルを閉じる
}

/*
テキストファイルに書き込む
*/
void writeFile(arrayTwo *array){
    
    FILE *fp;
    int i,j;

	fp = fopen(WRITEFILENAME, "w");
    if(fp == NULL) return ;

    fprintf(fp, "%d\n", array->dimension);
    fprintf(fp, "%d\n", array->size);

    for(i = 0; i <array->size; i++){
        for(j = 0; j < array->dimension; j++){
            fprintf(fp, "%f", array->data[i][j]);
            if(i != array->size - 1 || j != array->dimension - 1) fprintf(fp, "\n");
        }
    }

	fclose(fp);
}