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
### Pseudocode of Integer Keys
```text
function myHashInt(int key,int m)
  if m <= 0 then
      return error "Table size m must be > 0"
  end if

  const A = 2654435761  // Knuth's multiplicative constant

  unsigned long long hash = key;

  hash = hash * A 

  index = hash mod m

  return index
  ```
#### Rationale
This design multiplies the key by Knuth’s constant A = 2654435761 to spread nearby keys apart before applying mod m.
The idea is to:
- first spread nearby keys apart by multiplying with a large odd constant,
- then fold the result back into [0, m - 1] via mod m.

### Pseudocode of String Keys
```text
  function myHashString(string key,int m)
    if m <= 0 then
        raise error "Table size m must be > 0"
    end if

    if str is empty then
        raise error "String size must be > 0"
    end if

    unsigned hash = 0

    for each character ch in str do
        hash = hash + int(ch)  
    end for

    const A = 2654435761

    hash = hash * A

    index = hash mod m

    return int(index)
```
#### Rationale
The string is first reduced to a numeric value by summing character codes.Then multiplies the results by Knuth’s constant A = 2654435761 to spread nearby keys apart before applying mod m.
The idea is to:
- first reduce the string to a single numeric value
- second spread nearby keys apart by multiplying with a large odd constant,
- then fold the result back into [0, m - 1] via mod m.

### Design B: Squared Hashing
This second design modifies the previous idea by applying a square operation before taking mod m. The goal is to see how an additional non-linear step affects the distribution.
### Pseudocode of Integer Keys
```text
function myHashInt(int key,int m)
  if m <= 0 then
      return error "Table size m must be > 0"
  end if

  unsigned long long hash = key;

  hash = hash * hash 

  index = hash mod m

  return index
  ```
#### Rationale
This method uses h(k) = k² mod m to introduce a nonlinear transformation.
The key idea is:
- amplify the difference between keys by squaring them (k^2),
- then apply mod m to map them into the table.

### Pseudocode of String Keys
```text
  function myHashString(string key,int m)
    if m <= 0 then
        raise error "Table size m must be > 0"
    end if

    if str is empty then
        raise error "String size must be > 0"
    end if

    unsigned hash = 0

    for each character ch in str do
        hash = hash + int(ch)  
    end for

    hash = hash * hash

    index = hash mod m

    return int(index)
```
#### Rationale
The string is first reduced to a numeric value by summing character codes.Then use h(k) = k² mod m to introduce a nonlinear transformation.
The key idea is:
- first reduce the string to a single numeric value
- second amplify the difference between keys by squaring them (k^2),
- then apply mod m to map them into the table.

## Experimental Setup
This project evaluates the behavior of two hash function designs under different table sizes and datasets.
### Table Sizes Tested (m)
#### - 10
#### - 11 (prime number)
#### - 37 (prime number)
### Test Dataset
#### Integer Keys
```test
21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
51, 52, 53, 54, 55, 56, 57, 58, 59, 60
```
#### String Keys
```test
"cat", "dog", "bat", "cow", "ant",
"owl", "bee", "hen", "pig", "fox"
```