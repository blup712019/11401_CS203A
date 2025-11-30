/*
   ========================================
   hash_fn.c — implement your hash functions (C version)
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/23: Initialization
    - 2025/11/23: Added string-hash implementation
    - 2025/11/23: Change to multiplicative hashing
    - 2025/11/24: Modify hashing to hash^2 mod m
    - 2025/11/30: Converted to pure C version

   Developer: YI-FENG HUANG <s1123301@mail.yzu.edu.tw>
 */

#include "hash_fn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Computes the hash index for an integer key using:
 *          h(k) = (k^2) mod m
 *
 * @param key  Key to be hashed.
 * @param m    The hash table size. Must > 0.
 * @return     The computed hash index in the range [0, m - 1].
 *
 * @note In C version, invalid arguments will cause program exit.
 */
int myHashInt(int key, int m) {
    if (m <= 0) {
        fprintf(stderr, "Error: Table size m must be > 0\n");
        exit(EXIT_FAILURE);
    }

    unsigned long long hash = (unsigned long long)key;

    // 使用平方 hash
    hash = hash * hash;

    return (int)(hash % (unsigned long long)m);
}


/**
 * @brief Computes the hash index for a string key using additive + multiplicative hashing.
 *
 * The function first accumulates the sum of all character codes in the string,
 * then:
 *      h(str) = ( sum(str[i])^2 ) mod m
 * This helps spread string keys more uniformly across the table.
 *
 * @param str  The string key to be hashed. Must not be empty.
 * @param m    The hash table size. Must > 0.
 * @return     The computed hash index in the range [0, m - 1].
 *
 * @note In C version, invalid arguments will cause program exit.
 */
int myHashString(const char* str, int m) {
    if (m <= 0) { // 避免不合法的 table size
        fprintf(stderr, "Error: Table size m must be > 0\n");
        exit(EXIT_FAILURE);
    }
    if (str == NULL || strlen(str) == 0) { // 避免空字串 
        fprintf(stderr, "Error: String must not be empty\n");
        exit(EXIT_FAILURE);
    }

    unsigned long long hash = 0;
    
    // 將每個字元轉數字，加總當作 key 
    for (size_t i = 0; str[i] != '\0'; i++) {
        hash += (unsigned long long)(unsigned char)str[i];
    }

    // 使用平方 hash
    hash = hash * hash;

    return (int)(hash % (unsigned long long)m);
}
