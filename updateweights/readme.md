### Update Weights Code
το κομμάτι του κώδικα για τον υπολογισμό των παραμέτρων (W) του νευρωνικού δικτύου.  
αρχικοποίηση  τιμών εισόδου `Χ[60000][784]={{1,2,...,784},...,{1,2,...,784}}`  
έξοδοι 1ο Layer `OL1[100] = {1,2...100}`.  
`DL1[100] = {1,2...100}`  
`DL2[ 10] = {1,2... 10} `  
`α=0.01`

Στο τέλος των επαναλήψεων περιμένουμε τα βάρη να περιέχουν τις τιμές 
`W[i][j] = (i+1)*0.01*(j+1)*60000`



## Serial

```
$ nvc updateweights.c -o updateweights -Minfo=all 
updateweight:
    106, FMA (fused multiply-add) instruction(s) generated
    108, FMA (fused multiply-add) instruction(s) generated

$ time ./updateweights
X[60000][784], WL1[100][785] - WL2[10][101]
OL1[100] - DL1[100] - DL2[10]
DONE!

real    0m14,787s
user    0m14,580s
sys     0m0,172s
```

## Using Kernels Construct

```
$ nvc updateweights-kernels.c -o updateweights-kernels -Minfo=all -acc -ta=tesla
updateweight:
    104, Generating implicit copyin(delta[:n],input[:k]) [if not already present]
         Generating implicit copy(W[:n][:k+1]) [if not already present]
    105, Complex loop carried dependence of W->,delta->,input-> prevents parallelization
         Loop carried dependence of W-> prevents parallelization
         Loop carried backward dependence of W-> prevents vectorization
         Generating Tesla code
        105, #pragma acc loop seq
        107, #pragma acc loop seq
    107, Complex loop carried dependence of input->,W-> prevents parallelization
    112, Complex loop carried dependence of delta-> prevents parallelization
         Loop carried dependence of W-> prevents parallelization
         Loop carried backward dependence of W-> prevents vectorization
         Accelerator serial kernel generated
         Generating Tesla code
        112, #pragma acc loop seq
```

ο compiler δεν παραλληλοποιεί το κομμάτι του κώδικα που βρίσκεται ανάμεσα στις αγκύλες, θεωρεί πως υπάρχει εξάρτηση δεδομένων στον στον πίνακα W

## Parallel Construct

αρχείο updateweights-parallel.c  

```
$ nvc updateweights-parallel.c -o updateweights-parallel -Minfo=all -acc -ta=tesla
updateweight:
     98, Generating Tesla code
        104, #pragma acc loop gang, vector(128) /* blockIdx.x threadIdx.x */
        106, #pragma acc loop seq
     98, Generating implicit copyin(delta[:n],input[:k]) [if not already present]
         Generating implicit copy(W[:n][:k]) [if not already present]
    106, Complex loop carried dependence of input->,W-> prevents parallelization
    109, Generating Tesla code
        112, #pragma acc loop gang, vector(128) /* blockIdx.x threadIdx.x */
    109, Generating implicit copy(W[:n][k]) [if not already present]
         Generating implicit copyin(delta[:n]) [if not already present]

$ time ./updateweights-parallel 
X[60000][784], WL1[100][785] - WL2[10][101]
OL1[100] - DL1[100] - DL2[10]
DONE!

real    2m3,439s
user    2m2,811s
sys     0m0,428s
```

δεν γίνεται παραλληλοποίηση στον εσωτερικό βρόχο.    
```c
#pragma acc parallel loop 
 for(int i=0;i<n;i++){
        double temp=delta[i];
        for(int j=0;j<k;j++){
            W[i][j] += a*temp*input[j]; 
        }        
    }
```
δίνουμε την πληροφορία στον compiler προσθέτοντας loop construct  

```c
#pragma acc parallel loop 
    for(int i=0;i<n;i++){
        double temp=delta[i];
#pragma acc loop
        for(int j=0;j<k;j++){
            W[i][j] += a*temp*input[j]; 
        }        
    }
```


