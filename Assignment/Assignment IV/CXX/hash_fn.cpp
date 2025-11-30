/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file provides the implementations of hashing functions for integer
    and string keys, using Knuth's multiplicative hashing method. These 
    functions generate hash indices for use in hash table operations, and 
    include basic error checking to ensure valid inputs.

   Development History:
    - 2025/11/23: Initialization
    - 2025/11/23: Added string-hash implementation
    - 2025/11/23: Change to multiplicative hashing


   Developer: YI-FENG HUANG <s1123301@mail.yzu.edu.tw>
 */
#include "hash_fn.hpp"
#include <stdexcept>
// 使用Knuth multiplicative constant
#define A 2654435761ULL 

/**
 * @brief Computes the hash index for an integer key by using multiplicative hashing.
 *
 * This function is applied by Knuth's multiplicative hashing method:
 *      h(k) = (A * k) mod m
 * where A = 2654435761
 *
 * @param key  Key to be hashed.
 * @param m    The hash table size. Must > 0.
 * @return     The computed hash index in the range [0, m - 1].
 *
 * @throws std::invalid_argument if m <= 0.
 */
int myHashInt(int key, int m) {
    if (m <= 0) { // 避免不合法的table size
        throw std::invalid_argument("Table size m must be > 0");
    }


    unsigned long long hash = static_cast<unsigned long long>(key); 
    hash = hash * A; // 乘以A來達到發散的效果
    return static_cast<int>(hash % static_cast<unsigned long long>(m));  // 安全轉型
}


/**
 * @brief Computes the hash index for a string key using additive + multiplicative hashing.
 *
 * The function first accumulates the sum of all character codes in the string,
 * then applies the same multiplicative constant A:
 *      h(str) = ( sum(str[i]) * A ) mod m
 * This helps spread string keys more uniformly across the table.
 *
 * @param str  The string key to be hashed. Must not be empty.
 * @param m    The hash table size. Must > 0.
 * @return     The computed hash index in the range [0, m - 1].
 *
 * @throws std::invalid_argument if m <= 0 or str is empty.
 */
int myHashString(const std::string& str, int m) {
    if (m <= 0) {//避免不合法的table size
        throw std::invalid_argument("Table size m must be > 0");
    }
    if (str.empty()) {//避免空字串
        throw std::invalid_argument("String size must be > 0");
    }


    unsigned long long hash = 0;
    for(auto i: str){   // 直接把每個字元轉數字 加總當作key
        hash = hash +static_cast<int>(i);
    }
    hash = hash * A; // 乘以A來達到發散的效果
    return static_cast<int>(hash % static_cast<unsigned long long>(m));  // 安全轉型
}
