### Update Weights Code
το κομμάτι του κώδικα για τον υπολογισμό των παραμέτρων (W) του νευρωνικού δικτύου.  
αρχικοποίηση  τιμών εισόδου `Χ[60000][784]={{1,2,...,784},...,{1,2,...,784}}`  
έξοδοι 1ο Layer `OL1[100] = {1,2...100}`.  
`DL1[100] = {1,2...100}`  
`DL2[ 10] = {1,2... 10} ` 



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

