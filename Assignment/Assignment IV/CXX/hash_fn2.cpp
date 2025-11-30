/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file implements the hashing functions for integer and string keys
    used in the hash table module. The hashing method applies a square
    hashing approach, where both integer keys and the additive-sum form of 
    string keys are squared and then reduced modulo m.

   Development History:
    - 2025/11/23: Initialization
    - 2025/11/23: Added string-hash implementation
    - 2025/11/23: Change to multiplicative hashing
    - 2025/11/24: Modify hashing to hash^2 mod m


   Developer: YI-FENG HUANG <s1123301@mail.yzu.edu.tw>
 */
#include "hash_fn2.hpp"
#include <stdexcept>


/**
 * @brief Computes the hash index for an integer key using:
 *          h(k) = (k^2) mod m
 *
 * @param key  Key to be hashed.
 * @param m    The hash table size. Must > 0.
 * @return     The computed hash index in the range [0, m - 1].
 *
 * @throws std::invalid_argument if m <= 0.
 */

int myHashInt(int key, int m) {
    if (m <= 0) {
        throw std::invalid_argument("Table size m must be > 0");
    }

    unsigned long long hash = static_cast<unsigned long long>(key);

    // 使用平方 hash
    hash = hash * hash;

    return static_cast<int>(hash % static_cast<unsigned long long>(m));
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
    // 使用平方 hash
    hash = hash * hash;
    return static_cast<int>(hash % static_cast<unsigned long long>(m));  // 安全轉型
}
