# Introduction
This project aims to investigate the performance difference between x86-64 assembly language and C programming language implementations of a 1-D stencil operation.

# Description of the program
The program requires an integer scalar variable, _ _n_ _, denoting the length of the vectors. Both vectors _ _X_ _ and _ _Y_ _ are of double-precision float type. The stencil operation is defined as ![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/cacefc6f-98a6-4354-a432-2f6868c70140). It is important to note that the program restricts the value of _ _n_ _ to be greater than or equal to 8, due to the nature of the operation. Additionally, for the program's purpose, vector _ _X_ _ is initialized to contain values ranging from 0 to n-1.

# Algorithm implementation
The algorithm is basically a moving window sum with the window size of 7. This involves iterating over vector _ _X _ _ _ _n - 6_ _ times, shifting the window one position to the right with each iteration to generate the sequence to be stored in vector _ _Y_ _.

# Sanity Check
![image](https://github.com/Tiny-Banana/LBYARCH-MP2/assets/89186133/f4327e28-ee16-4caf-ab83-f85f4d13c80e)
The program includes a sanity check to verify the correctness of both the C and assembly implementations. If the sanity check detects inconsistencies between the outputs of these implementations, signaling a potential error, the program promptly terminates to ensure the reliability of the results.

