# Homework Assignment IV: Hash Function Design & Observation (C/C++ Version)

Developer: YI-FENG HUANG
Email: Blup712019@gmail.com 
## Environment
This project is developed and executed on a Windows environment using the MinGW-W64 toolchain to compile both C and C++ implementations.
The compiler versions used in this project are:
```text
  g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders) 14.3.0
  gcc.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders) 14.3.0
  ```
  Key characteristics:
  - Compiler Versions: GCC 14.3.0 (C), G++ 14.3.0 (C++)
  - Build System: Windows batch-based Makefile.bat for compilation automation

## Hash Function Design and Pseudocode
In this project I implemented two different hash function for both integer keys and string keys to compare their performance in terms of collision rate and distribution uniformity:
1. Design A – Multiplicative hashing (Knuth’s method)


2. Design B – Squared hashing (hash^2 mod m)


Both designs share the same overall goal:
- mapping keys into the range [0, m - 1],
- reduce clustering patterns,
- and make it easier to compare how table size m affects the distribution of indices in different design.
### Design A: Multiplicative Hashing (Knuth’s Method)