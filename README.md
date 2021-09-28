# parallel-programming


[**nn1-5.c**](https://github.com/olia92/NeuralNetwork.git)  Νευρωνικό Δίκτυο, τυχαίες τιμές παραδειγμάτων. 

---

## Updateweights Serial

```
$ gcc -o updateweights updateweights-omp1.c

$ time ./updateweights
DONE!

real    0m0,006s
user    0m0,000s
sys     0m0,007s

```

## OpenACC
```
$ nvc -acc -ta:tesla -o updateweights-acc updateweights-acc.c -Minfo=all
main:
     37, Generating create(X[:]) [if not already present]
         Generating copyout(WL2[:][:]) [if not already present]
         Generating create(DL2[:],DL1[:],OL1[:]) [if not already present]
         Generating copyout(WL1[:][:]) [if not already present]
Initialise_X:
     56, Generating present(X[:])
         Generating Tesla code
         60, #pragma acc loop gang /* blockIdx.x */
     62, Generating present(OL1[:])
         Generating Tesla code
         64, #pragma acc loop gang, vector(96) /* blockIdx.x threadIdx.x */
     65, Generating present(DL1[:])
         Generating Tesla code
         69, #pragma acc loop gang, vector(96) /* blockIdx.x threadIdx.x */
     70, Generating present(DL2[:])
         Generating Tesla code
         74, #pragma acc loop gang /* blockIdx.x */
updateweight:
     93, Generating present(delta[:n],input[:k],W[:n][:k+1])
         Generating Tesla code
         99, #pragma acc loop gang, vector(128) /* blockIdx.x threadIdx.x */
        101, #pragma acc loop seq
    101, Complex loop carried dependence of input->,W-> prevents parallelization

$ time ./updateweights-acc 
DONE!

real    0m0,180s
user    0m0,017s
sys     0m0,145s
```

---

## OpenMP

### updateweights-omp1: parallel for

```
$ gcc -o updateweights-omp1 updateweights-omp1.c -fopenmp 
$ time ./updateweights-omp1 
DONE!

real    0m0,021s
user    0m0,046s
sys     0m0,000s

```

### updateweights-omp2: sections

```
$ gcc -o updateweights-omp2 updateweights-omp2.c -fopenmp 

$ time ./updateweights-omp2
DONE!

real    0m0,016s
user    0m0,027s
sys     0m0,004s

```
