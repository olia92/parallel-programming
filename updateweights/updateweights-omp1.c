//*****************************
/*
    Neural Network
    2 layers 
*/
//*****************************

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "printing.h"

// *******************************************************************
// #pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
// #pragma GCC option("arch=native","tune=native","no-zero-upper")
//************************************************************

#define NL1 100//hidden Layer
#define NL2 10//Output
#define N 12 //Input
#define M 1//Number of inputs-outputs

#define a 1

//---------------------
double X[N];
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
    // SaveWeightsToFile("X_1.csv",M,N,X);
    SaveWeightsToFile("W1_1.csv",NL1,N+1,WL1);
    SaveWeightsToFile("W2_1.csv",NL2,NL1+1,WL2);


    Initialise_X();
    // Initialise_W();
    // SaveWeightsToFile("X_2.csv",M,N,X);

    updateweight(NL2,NL1,WL2,OL1,DL2);
    updateweight(NL1,N,WL1,X,DL1);

    SaveWeightsToFile("W1_2.csv",NL1,N+1,WL1);
    SaveWeightsToFile("W2_2.csv",NL2,NL1+1,WL2);

    printf("DONE!\n");
    return 0;
}

//*********************************************************
void Initialise_X(){

#pragma omp parallel for
    for (int i=0;i<N;i++)
        X[i]=i+1;

#pragma omp parallel for
for (int i=0;i<NL1;i++)
        OL1[i]=i+1;

#pragma omp parallel for
    for (int i=0;i<NL1;i++)
        DL1[i]=i+1;

#pragma omp parallel for
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
// #pragma omp parallel for 
    for(int i=0;i<n;i++){
        double temp=delta[i];
#pragma omp parallel for schedule(static,100)
// #pragma omp parallel for schedule(dynamic)
        for(int j=0;j<k;j++){
            W[i][j] += a*temp*input[j]; 
        }        
        W[i][k] += a*temp;//bias update
    }
}

