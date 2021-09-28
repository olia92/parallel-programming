#ifndef HEADER_FILE_NAME
#define HEADER_FILE_NAME

#include <stdio.h>

#define PRINT_STEP 1


//*********************************************************
void PrintArray(int n,double a[]){

    for (int i=0;i<n;i+=PRINT_STEP)
            printf("%6.2lf ",a[i]);
        printf("\n");
}

void Print2dArray(int n,int m,double a[][m]){

    for (int i=0;i<n;i+=PRINT_STEP){
        for (int j=0;j<m;j+=PRINT_STEP)
            printf("%6.2lf ",a[i][j]);
        printf("\n");
        }
}

//*********************************************************

void SaveWeightsToFile(char *fileName,int n,int m,double w[][m]){

FILE *filePointer ; 

filePointer = fopen(fileName, "w");

fprintf(filePointer, "WL1[%d][%d]\n",n,m);
for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        fprintf(filePointer,"%lf, ",w[i][j]);
    }
    fprintf(filePointer,"\n");
}

fclose(filePointer);
    
}

#endif

