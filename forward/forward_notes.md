## forward.c

```
$ gcc -o fw forward.c -ml
$ time ./fw 
X[60000][784], WL1[100][785] - WL2[10][101]
           OL1[100]     - OL2[10]
DONE!

real    0m43,760s
user    0m41,569s
sys     0m1,250s
```
---

# OpenMP
## forward-opm.c 
##### 
|parallel for private(sum)|parallel for private(sum) <br> schedule(static, 100) |parallel for private(sum) <br> schedule(static, 10) |
|---                      |---               |---               |
|real    0m33,699s        |real    0m48,522s |real    0m33,485s |
|user    1m17,040s        |user    2m10,050s |user    1m15,889s |
|sys      0m0,986s        |sys      0m1,145s |sys      0m1,078s |

```
$ gcc -o fw forward-omp.c -lm -fopenmp
$ time ./fw 
X[60000][784], WL1[100][785] - WL2[10][101]
           OL1[100]     - OL2[10]
DONE!

real    0m33,699s
user    1m17,040s
sys     0m0,986s

```
---

## OpenACC

### #pragma acc kernels
```
$ nvc -acc -o fw -ta=tesla forward-acc.c -Minfo=all
sigmoid:
     33, Generating implicit acc routine seq
         Generating acc routine seq
         Generating Tesla code
Initialise_W:
    105, FMA (fused multiply-add) instruction(s) generated
    109, FMA (fused multiply-add) instruction(s) generated
forward:
    122, Generating implicit copyout(y[:n]) [if not already present]
         Generating implicit copyin(x[:m],w[:n][:m+1]) [if not already present]
    123, Complex loop carried dependence of w-> prevents parallelization
         Loop carried dependence of y-> prevents parallelization
         Loop carried backward dependence of y-> prevents vectorization
         Complex loop carried dependence of x-> prevents parallelization
         Generating Tesla code
        123, #pragma acc loop seq
        125, #pragma acc loop vector(128) /* threadIdx.x */
             Generating implicit reduction(+:sum)
    125, Loop is parallelizable

$ time ./fw 
X[60000][784], WL1[100][785] - WL2[10][101]
OL1[100] - OL2[10]
DONE!

real    1m31,069s
user    1m28,518s
sys     0m1,159s

```
---
### #pragma acc parallel loop 

```
$ nvc -acc -o fw -ta=tesla forward-acc.c -Minfo=all
sigmoid:
     33, Generating implicit acc routine seq
         Generating acc routine seq
         Generating Tesla code
Initialise_W:
    105, FMA (fused multiply-add) instruction(s) generated
    109, FMA (fused multiply-add) instruction(s) generated
forward:
    120, Generating Tesla code
        124, #pragma acc loop gang /* blockIdx.x */
        126, #pragma acc loop vector(128) /* threadIdx.x */
             Generating implicit reduction(+:sum)
    120, Generating implicit copyout(y[:n]) [if not already present]
         Generating implicit copyin(x[:m],w[:n][:m+1]) [if not already present]
    126, Loop is parallelizable

$ time ./fw 
X[60000][784], WL1[100][785] - WL2[10][101]
OL1[100] - OL2[10]
DONE!

real    0m54,386s
user    0m51,799s
sys     0m1,323s
```
### -Msafeptr -> Loop is parallelizable

```
$ nvc -acc -o fw -ta=tesla forward-acc.kernels.c -Minfo=all -Msafeptr && time ./fw
sigmoid:
     33, Generating implicit acc routine seq
         Generating acc routine seq
         Generating Tesla code
Initialise_W:
    104, FMA (fused multiply-add) instruction(s) generated
    108, FMA (fused multiply-add) instruction(s) generated
forward:
    121, Generating implicit copyin(x[:m]) [if not already present]
         Generating implicit copyout(y[:n]) [if not already present]
         Generating implicit copyin(w[:n][:m+1]) [if not already present]
    123, Loop is parallelizable
         Generating Tesla code
        123, #pragma acc loop gang /* blockIdx.x */
        126, #pragma acc loop vector(128) /* threadIdx.x */
             Generating reduction(+:sum)
    126, Loop is parallelizable
X[60000][784], WL1[100][785] - WL2[10][101]
OL1[100] - OL2[10]
DONE!

real    0m55,094s
user    0m53,182s
sys     0m1,291s
```

```
$ nvc -acc -o fw -ta=tesla forward-acc.parallel.c -Minfo=all -Msafeptr && time ./fwsigmoid:
     33, Generating implicit acc routine seq
         Generating acc routine seq
         Generating Tesla code
Initialise_W:
    104, FMA (fused multiply-add) instruction(s) generated
    108, FMA (fused multiply-add) instruction(s) generated
forward:
    119, Generating Tesla code
        121, #pragma acc loop gang /* blockIdx.x */
        123, #pragma acc loop vector(128) /* threadIdx.x */
             Generating implicit reduction(+:sum)
    119, Generating implicit copyout(y[:n]) [if not already present]
         Generating implicit copyin(x[:m],w[:n][:m+1]) [if not already present]
    123, Loop is parallelizable
X[60000][784], WL1[100][785] - WL2[10][101]
OL1[100] - OL2[10]
DONE!

real    0m59,191s
user    0m57,100s
sys     0m1,267s
```