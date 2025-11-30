/*
   ========================================
   hash_fn.c — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation
    - 2025/11/17: Refactored to use hash_fn.h
    - 2025/11/24: Implementation C version
   Developer: YI-FENG HUANG <s1123301@mail.yzu.edu.tw>
 */

#include "hash_fn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define A 2654435761ULL // 使用 Knuth multiplicative constant 

/**
 * @brief Computes the hash index for an integer key by using multiplicative hashing.
 *
 * This function is applied by Knuth's multiplicative hashing method:
 *      h(k) = (A * k) mod m
 * where A = 2654435761
 *
 * @param key  Key to be hashed.
 * @param m    The hash table size. Must > 0.
 * @return     The computed hash index in the range [0, m - 1], or -1 on error.
 *
 * Error handling:
 *   - if m <= 0:
 *       - prints error message to stderr
 *       - sets errno = EINVAL
 *       - returns -1
 */

    int myHashInt(int key, int m) {
    if (m <= 0) { // 避免不合法的 table size
        fprintf(stderr, "myHashInt error: table size m must be > 0\n");
        errno = EINVAL;
        return -1;
    }

    // 轉成 unsigned 避免符號延伸問題
    unsigned long long hash = (unsigned long long)(unsigned int)key;
    hash = hash * A; // 乘以 A 來達到發散效果

    return (int)(hash % (unsigned long long)m);
}

/**
 * @brief Computes the hash index for a string key using additive + multiplicative hashing.
 *
 * The function first accumulates the sum of all character codes in the string,
 * then applies the same multiplicative constant A:
 *      h(str) = ( sum(str[i]) * A ) mod m
 * This helps spread string keys more uniformly across the table.
 *
 * @param str  The C-string key to be hashed. Must not be NULL or empty.
 * @param m    The hash table size. Must > 0.
 * @return     The computed hash index in the range [0, m - 1], or -1 on error.
 *
 * Error handling:
 *   - if m <= 0:
 *       - prints error message to stderr
 *       - sets errno = EINVAL
 *       - returns -1
 *   - if str == NULL or str is empty:
 *       - prints error message to stderr
 *       - sets errno = EINVAL
 *       - returns -1
 */

int myHashString(const char *str, int m) {
    if (m <= 0) { // 避免不合法的 table size 
        fprintf(stderr, "myHashString error: table size m must be > 0\n");
        errno = EINVAL;
        return -1;
    }

    if (str == NULL || str[0] == '\0') { // 避免 NULL 或空字串 
        fprintf(stderr, "myHashString error: string must not be NULL or empty\n");
        errno = EINVAL;
        return -1;
    }

    unsigned long long hash = 0;
    unsigned char *p = (unsigned char *)str;
    // 把每個字元轉成數字加總當作 key
    while (*p != '\0') {
        hash += (unsigned long long)(*p);
        ++p;
    }

    hash = hash * A; // 乘以 A 來達到發散效果

    return (int)(hash % (unsigned long long)m);
}
