$ nvc updateweights.c -o updateweights -acc -ta:tesla -Minfo=all 
main:
     47, Generating create(X[:]) [if not already present]
         Generating copyout(WL2[:][:]) [if not already present]
         Generating create(DL2[:],DL1[:],OL1[:]) [if not already present]
         Generating copyout(WL1[:][:]) [if not already present]
Initialise_X:
     68, Generating present(X[:])
         Generating Tesla code
         72, #pragma acc loop gang /* blockIdx.x */
     74, Generating present(OL1[:])
         Generating Tesla code
         76, #pragma acc loop gang, vector(96) /* blockIdx.x threadIdx.x */
     77, Generating present(DL1[:])
         Generating Tesla code
         81, #pragma acc loop gang, vector(96) /* blockIdx.x threadIdx.x */
     82, Generating present(DL2[:])
         Generating Tesla code
         86, #pragma acc loop gang /* blockIdx.x */
updateweight:
    105, Generating present(delta[:n],input[:k],W[:n][:k+1])
         Generating Tesla code
        111, #pragma acc loop gang, vector(128) /* blockIdx.x threadIdx.x */
        113, #pragma acc loop seq
    113, Complex loop carried dependence of input->,W-> prevents parallelization
---

$ time ./updateweights
DONE!

real    0m0,204s
user    0m0,032s
sys     0m0,141s

---
