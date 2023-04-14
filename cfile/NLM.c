#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define H 0.00000000001
#define LIMIT 100000

void enter(double **data, int dimension, int size);
void enter_randam(double **data, int demnsion, int size);
void assignment(double **data1, double **data2, int demnsion, int size);
void print_array(double **data, int demension, int size);
double cal_error(double **BaseData, double **ModifiedData, int basedemen, int modifieddemen, int size);
double cal_distance(double *data1, double *data2, int dimension);
void autodifferen(double *partialdifferen, double **BaseData, double **ModifiedData, int basedemen, int modifieddemen, int size);
double differential(double **BaseData, double **ModifiedData, double **DeltaData, int basedemen, int modifieddemen, int size);
void extreme(double **BaseData, double **ModifiedData, int basedemen, int modifieddemen, int size);

int main(void){

    int i,j;
    int size = 5;
    int basedemen = 4;
    int modifieddemen = 2;
    double **BaseData;
    double **ModifiedData;

    double error;

    BaseData = (double**)malloc(sizeof(double*)*size);
    BaseData[0] = (double*)malloc(sizeof(double)*basedemen*size);
    if(BaseData == NULL) exit(0);
    for(i=1; i<size; i++){
        BaseData[i] = BaseData[i-1] + basedemen;
    }

    ModifiedData = (double**)malloc(sizeof(double*)*size);
    ModifiedData[0] = (double*)malloc(sizeof(double)*modifieddemen*size);
    if(ModifiedData == NULL) exit(0);
    for(i=1; i<size; i++){
        ModifiedData[i] = ModifiedData[i-1] + modifieddemen;
    }

    enter(BaseData, basedemen, size);
    enter_randam(ModifiedData, modifieddemen, size);

    print_array(BaseData, basedemen, size);
    print_array(ModifiedData, modifieddemen, size);

    extreme(BaseData, ModifiedData, basedemen, modifieddemen, size);

    free(BaseData);
    free(ModifiedData);
    

    return 0;
}


void enter(double **data, int demnsion, int size){
    
    int i,j;

    for(i=0;i<size;i++){
        for(j=0;j<demnsion;j++){
            data[i][j]=i*2;
        }
    }
}

void enter_randam(double **data, int demnsion, int size){
    
    int i,j;

    for(i=0;i<size;i++){
        for(j=0;j<demnsion;j++){
            data[i][j]=rand()%10;
        }
    }
}

void assignment(double **data1, double **data2, int demnsion, int size){
    
    int i,j;

    for(i=0;i<size;i++){
        for(j=0;j<demnsion;j++){
            data1[i][j]=data2[i][j];
        }
    }
}



void print_array(double **data, int demension, int size){
    
    int i, j;
    
    for(i=0;i<size;i++){
        for(j=0;j<demension;j++){
            printf("[%d,%d] = %f\n",i, j, data[i][j]);
        }
    }
    printf("\n");
}


double cal_error(double **BaseData, double **ModifiedData, int basedemen, int modifieddemen, int size){
    
    int i, j;
    double error;
    double dist_base, dist_modified;
    double sum_base = 0.0;
    double sum_modified = 0.0;

    for(i=0; i<size; i++){
        for(j=i+1; j<size; j++){
            dist_base = cal_distance(BaseData[i], BaseData[j], basedemen);
            dist_modified = cal_distance(ModifiedData[i], ModifiedData[j], modifieddemen);
            sum_base += dist_base;
            sum_modified += pow(dist_base-dist_modified,2.0) / dist_base;
        }
    }

    error = sum_base / sum_modified;

    return error;
}


double cal_distance(double *data1, double *data2, int demension){

    int i;
    double difference = 0.0;
    double sum = 0.0;
    double distance = 0.0;

    for(i=0; i<demension; i++){
        difference = data1[i];
        difference -= data2[i];
        sum += pow(difference,2.0);
    }

    distance = sqrt(sum);

    return distance;

}

void extreme(double **BaseData, double **ModifiedData, int basedemen, int modifieddemen, int size){

    int i,j;
    double *partialdifferen;

    partialdifferen = (double*)malloc(sizeof(double)*size*modifieddemen);
    if(partialdifferen == NULL) exit(0);

    double a = 0.5;
    double error = 10000;
    int count = 0;
    int count_partial = 0;

    while(count < LIMIT){
        count++;
        autodifferen(partialdifferen, BaseData, ModifiedData, basedemen, modifieddemen, size);
        count_partial = 0;
        for(i=0; i<size; i++){
            for(j=0; j<modifieddemen; j++){
                ModifiedData[i][j] -= a * partialdifferen[count_partial];
                count_partial++;
            }
        }
        error = fabs(cal_error(BaseData, ModifiedData, basedemen, modifieddemen, size));
        //printf("%d:%.32f\n", count, error);
    }

    print_array(ModifiedData, modifieddemen, size);

    free(partialdifferen);
}


void autodifferen(double *partialdifferen, double **BaseData, double **ModifiedData, int basedemen, int modifieddemen, int size){

    int i,j;
    int count_partial = 0;
    double **DeltaData;

    DeltaData = (double**)malloc(sizeof(double*)*size);
    DeltaData[0] = (double*)malloc(sizeof(double)*modifieddemen*size);
    if(DeltaData == NULL) exit(0);
    for(i=1; i<size; i++){
        DeltaData[i] = DeltaData[i-1] + modifieddemen;
    }
    //print_array(DeltaData, modifieddemen, size);
    assignment(DeltaData, ModifiedData, modifieddemen, size);

    for(i=0; i<size; i++){
        for(j=0; j<modifieddemen; j++){
            DeltaData[i][j] = ModifiedData[i][j] + H;
            partialdifferen[count_partial] = differential(BaseData, ModifiedData, DeltaData, basedemen, modifieddemen, size);
            DeltaData[i][j] = ModifiedData[i][j];
            count_partial ++;
        }
    }

    free(DeltaData);
}


double differential(double **BaseData, double **ModifiedData, double **DeltaData, int basedemen, int modifieddemen, int size){
    
    double fx;

    fx = (cal_error(BaseData, DeltaData, basedemen, modifieddemen, size) - cal_error(BaseData, ModifiedData, basedemen, modifieddemen, size)) / H;

    return fx;
}