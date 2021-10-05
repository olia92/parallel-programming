#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include "../headers/printing.h"

// *******************************************************************
// #pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
// #pragma GCC option("arch=native","tune=native","no-zero-upper")
//************************************************************

#define NL1 100//100//hidden Layer
#define NL2 10//10//Output
#define N 784//784 //Input
#define M 60000//Number of inputs-outputs

#define a -0.1

//---------------------
double X[M][N];
// double Y[M][NL2]={0};
double WL1[NL1][N+1]={0};
double WL2[NL2][NL1+1]={0};
double DL1[NL1];
double OL1[NL1];
double OL2[NL2]={0};

double DL2[NL2];

void Initialise_X();
void Initialise_W();
double sigmoid(double x){return (1.0/(1+exp(-x)));}
void forward(const int n,const int m,double w[n][m+1],double x[m],double y[n]);



int main(){
    // SaveWeightsToFile("../output_data/X_1.csv",M,N,X);
    // SaveWeightsToFile("../output_data/W1_1.csv",NL1,N+1,WL1);
    // SaveWeightsToFile("../output_data/W2_1.csv",NL2,NL1+1,WL2);

// #pragma acc data create(X[0:N],OL1[0:NL1],DL1[0:NL1],DL2[0:NL2]) copyout(WL1[0:NL1][0:N+1],WL2[0:NL2][0:NL1+1])
// {
printf("X[%d][%d], WL1[%d][%d] - WL2[%d][%d]\n",M,N,NL1,N+1,NL2,NL1+1);
printf("OL1[%d] - OL2[%d]\n",NL1,NL2);
    Initialise_X();
    SaveWeightsToFile("../output_data/X.csv",M,N,X);
    Initialise_W();
    // SaveWeightsToFile("../output_data/X_2.csv",M,N,X);
    SaveToFile("../output_data/OL1_1.csv",NL1,OL1);
    SaveToFile("../output_data/OL2_2.csv",NL2,OL2);

// }
    
    for(int m=0;m<M;m++){
        //calculte OL1
        forward(NL1,N,WL1,(double*)X[m],OL1);
        //calculte OL2
        forward(NL2,NL1,WL2,OL1,OL2);
    }
    SaveToFile("../output_data/OL1_2.csv",NL1,OL1);
    SaveToFile("../output_data/OL2_2.csv",NL2,OL2);


    // SaveWeightsToFile("../output_data/W1_2.csv",NL1,  N+1,WL1);
    // SaveWeightsToFile("../output_data/W2_2.csv",NL2,NL1+1,WL2);

    printf("DONE!\n");
    return 0;
}

//*********************************************************
void Initialise_X(){


// #pragma acc parallel loop present(X[0:N])
    for (int m=0;m<M;m++)
        for (int i=0;i<N;i++){
            X[m][i]=rand()/(double)RAND_MAX;
        }
// #pragma acc parallel loop present (OL1[0:NL1])
// for (int i=0;i<NL1;i++)
//         OL1[i]=i+1;


// #pragma acc parallel loop present (DL1[0:NL1])
//     for (int i=0;i<NL1;i++)
//         DL1[i]=i+1;


// #pragma acc parallel loop present (DL2[0:NL2])
//     for (int i=0;i<NL2;i++)
        // DL2[i]=i+1;

}

//*********************************************************

void Initialise_W(){

    for (int i=0;i<NL1;i++)
        for (int j=0;j<=N;j++)
            WL1[i][j]=(rand()/(double)RAND_MAX)*0.2-0.1;//j+1)*(i+1);

    for (int i=0;i<NL2;i++)
        for (int j=0;j<=NL1;j++)
            WL2[i][j]=(rand()/(double)RAND_MAX)*0.2-0.1;//(j+1)*(i+1);
}
//*********************************************************


void forward(const int n,const int m,double w[n][m+1],double x[m],double y[n]){
    // !!! W[n][m+1] !!! x[m]: inputs, y[n]: outputs
    //n : neuron number
    //m : inputs to neuron n
    //m+1: bias

    double sum;
#pragma acc kernels
{     
#pragma acc loop gang private(sum) 
    for (int i=0;i<n;i++){
        sum=w[i][m];//bias
#pragma acc loop vector reduction(+:sum)
        for(int j=0;j<m;j++){
            sum += w[i][j]*x[j];
        }
        y[i]=sigmoid(sum);
    }   
}
}
