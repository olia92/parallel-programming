```
$ nvcpuid 
vendor id       : GenuineIntel
model name      : Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz
cpu family      : 6
model           : 61
name            : Broadwell Core gen 5 M-5xxx
stepping        : 4
processors      : 4
threads         : 2
clflush size    : 8
L2 cache size   : 256KB
L3 cache size   : 3072KB
flags           : acpi aes apic avx avx2 cflush cmov cplds cx8 cx16 de dtes
flags           : f16c ferr fma fpu fxsr ht lm mca mce mmx monitor movbe msr
flags           : mtrr nx osxsave pae pat pdcm pge popcnt pse pseg36
flags           : selfsnoop speedstep sep sse sse2 sse3 ssse3 sse4.1 sse4.2
flags           : syscall tm tm2 tsc vme xsave xtpr
default target  : -tp haswell
```

```
$ nvaccelinfo 

CUDA Driver Version:           11040
NVRM version:                  NVIDIA UNIX x86_64 Kernel Module  470.103.01  Thu Jan  6 12:10:04 UTC 2022

Device Number:                 0
Device Name:                   NVIDIA GeForce 920M
Device Revision Number:        3.5
Global Memory Size:            2101739520
Number of Multiprocessors:     2
Concurrent Copy and Execution: Yes
Total Constant Memory:         65536
Total Shared Memory per Block: 49152
Registers per Block:           65536
Warp Size:                     32
Maximum Threads per Block:     1024
Maximum Block Dimensions:      1024, 1024, 64
Maximum Grid Dimensions:       2147483647 x 65535 x 65535
Maximum Memory Pitch:          2147483647B
Texture Alignment:             512B
Clock Rate:                    954 MHz
Execution Timeout:             Yes
Integrated Device:             No
Can Map Host Memory:           Yes
Compute Mode:                  default
Concurrent Kernels:            Yes
ECC Enabled:                   No
Memory Clock Rate:             900 MHz
Memory Bus Width:              64 bits
L2 Cache Size:                 524288 bytes
Max Threads Per SMP:           2048
Async Engines:                 1
Unified Addressing:            Yes
Managed Memory:                Yes
Concurrent Managed Memory:     No
Default Target:                cc35
```
