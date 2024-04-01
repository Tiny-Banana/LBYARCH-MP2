# Comparative analysis of the performance of the kernels in x86-64 and C

## Introduction
This project aims to investigate the performance difference between x86-64 assembly language and C programming language implementations of a 1-D stencil operation. The operation is defined as ![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/cacefc6f-98a6-4354-a432-2f6868c70140). 

## Description of the program
The program requires an integer scalar variable,  _n_, denoting the length of the vectors. Both vectors _X_  and _Y_  are of double-precision float type. It is important to note that the program restricts the value of _n_ to be greater than or equal to 8, due to the nature of the operation. Additionally, for the program's purpose, vector _X_  is initialized to contain values ranging from 0 to n-1.

## Algorithm implementation
The algorithm is basically a moving window sum with the window size of 7. This involves iterating over vector _X _   _n - 6__ times, shifting the window one position to the right with each iteration to generate the sequence to be stored in vector _Y_ .

## Sanity Check
![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/ecf851c6-4d30-4211-8f8c-5836ee8e3136)
The program includes a sanity check to verify the correctness of both the C and assembly kernels. If the sanity check detects inconsistencies between the outputs of these kernels, signaling a potential error, the program promptly terminates to ensure the reliability of the results.

## Analysis
### Input size 2<sup>20</sup>
| Debug Mode | Release Mode |
|----------|----------|
| ![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/f90baee2-d5f4-42e7-b86c-32b348068365) | ![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/f9b192ab-b1c8-4d53-aedc-d67029df4252)|

The x86-64 and C kernels demonstrate average execution times of 0.017967 seconds and 0.037467 seconds, respectively, in debug mode. In release mode, the execution times are 0.017467 seconds for x86-64 and 0.006600 seconds for C.


### Input size 2<sup>24</sup>
| Debug Mode | Release Mode |
|----------|----------|
| ![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/445c9f41-759a-4a5d-8777-d4061f0f6b48)| ![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/b5fd1846-68c3-4de2-a039-f870ff98228c)|

The x86-64 and C kernels demonstrate average execution times of 0.290933 seconds and 0.685533 seconds, respectively, in debug mode. In release mode, the execution times are 0.283967 seconds for x86-64 and  0.111433 seconds for C.

### Input size 2<sup>28</sup>
| Debug Mode | Release Mode |
|----------|----------|
|![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/eb1596a0-ff55-481c-82b0-e120eff47f44) |![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/25496553-83cc-49bf-9a36-e78d12e4e5c4)|

The x86-64 and C kernels demonstrate average execution times of 6.144167 seconds and 17.325333 seconds, respectively, in debug mode. In release mode, the execution times are 20.930033 seconds for x86-64 and  4.449600 seconds for C.

### Comparison
Based on the analysis, there's a significant difference in execution times between debug and release modes. Debug mode tends to have considerably longer execution times, which is expected due to the additional debugging information and enabled optimizations. In debugging mode, the x86-64 kernel consistently outperforms the C kernel across all input sizes. However, in release mode, the situation reverses, with the C kernel surpassing the x86-64 kernel in performance, which can be attributed to optimization features inherent in C when operating in release mode.

In conclusion, in situations where maximum performance is critical and fine-grained control over hardware resources is required, assembly language can be more suitable, for it allows developers to optimize code at the instruction level, resulting in highly efficient and tailored solutions. However, it's worth noting that modern compilers have made significant advancements in optimization techniques, narrowing the performance gap between assembly language and higher-level languages like C. As demonstrated in the analysis, the release mode results showcase the effectiveness of compiler optimizations in improving the performance of C kernel, sometimes even surpassing that of the x86-64 kernel. Ultimately, the choice between assembly and higher-level languages hinges on a careful consideration of performance requirements, development constraints, and the trade-offs between control and productivity.
