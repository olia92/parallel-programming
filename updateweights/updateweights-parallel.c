#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include "../headers/printing.h"

//************************************************************

#define NL1 100//100//hidden Layer
#define NL2 10//10//Output
#define N 12//784 //Input
#define M 1//60000//Number of inputs-outputs

#define a 0.01

//---------------------
double X[M][N];
// double Y[M][NL2]={0};
double WL1[NL1][N+1]={0};
double WL2[NL2][NL1+1]={0};
double DL1[NL1];
double OL1[NL1];
double DL2[NL2];

void Initialise_X();
void Initialise_W();
void updateweight(const int n,const int k,double W[n][k+1],double input[k],double delta[n]);


int main(){

printf("X[%d][%d], WL1[%d][%d] - WL2[%d][%d]\n",M,N,NL1,N+1,NL2,NL1+1);
printf("OL1[%d] - DL1[%d] - DL2[%d]\n",NL1,NL1,NL2);

    SaveWeightsToFile("W1_1.csv",NL1,N+1,WL1);
    SaveWeightsToFile("W2_1.csv",NL2,NL1+1,WL2);




    Initialise_X();
    // Initialise_W();
for(int m=0;m<M;m++){
    updateweight(NL2,NL1,WL2,OL1,DL2);
    updateweight(NL1,N,WL1,(double*)X[m],DL1);
}


    SaveWeightsToFile("W1_2.csv",NL1,N+1,WL1);
    SaveWeightsToFile("W2_2.csv",NL2,NL1+1,WL2);

    // PrintArray(20,OL1);
// printf("%lf,%lf,%lf/n",WL1[0][0],WL1[0][1],WL1[0][2]);
    printf("DONE!\n");
    return 0;
}

//*********************************************************
void Initialise_X(){



for (int j=0;j<M;j++)
    for (int i=0;i<N;i++){
        X[j][i]=i+1;
     }

for (int i=0;i<NL1;i++)
        OL1[i]=i+1;



    for (int i=0;i<NL1;i++)
        DL1[i]=i+1;



    for (int i=0;i<NL2;i++)
        DL2[i]=i+1;

}

//*********************************************************

// void Initialise_W(){
// #pragma acc data create(WL1[:NL1][:N+1])
// {
// #pragma acc parallel loop present( WL1[:NL1][:N+1] )
//     for (int j=0;j<=N;j++)
//         for (int i=0;i<NL1;i++)
//             WL1[i][j]=0;
// }
// }
//*********************************************************


void updateweight(const int n,const int k,double W[n][k+1],double input[k],double delta[n]){
    // !!! W[n][k+1] !!!
    //n : number of neurons output layer
    //k : input layer

#pragma acc parallel loop 
    for(int i=0;i<n;i++){
        double temp=delta[i];
        for(int j=0;j<k;j++){
            W[i][j] += a*temp*input[j]; 
        }        
    }

#pragma acc parallel loop 
    for(int i=0;i<n;i++){
        double temp=delta[i];       
        W[i][k] += a*temp;//bias update
    }
}

