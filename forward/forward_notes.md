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
