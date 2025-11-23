/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/23: Initialization
    - 2025/11/23: Added string-hash implementation
    - 2025/11/23: Change to multiplicative hashing


   Developer: YI-FENG HUANG <s1123301@mail.yzu.edu.tw>
 */
#include "hash_fn.hpp"
#include <stdexcept>
#define A 2654435761ULL //使用Knuth multiplicative constant


int myHashInt(int key, int m) {
    if (m <= 0) { //避免不合法的table size
        throw std::invalid_argument("Table size m must be > 0");
    }


    unsigned long long hash = static_cast<unsigned long long>(key); 
    hash = hash * A; //乘以A來達到發散的效果
    return static_cast<int>(hash % static_cast<unsigned long long>(m));  // 安全轉型
}

int myHashString(const std::string& str, int m) {
    if (m <= 0) {//避免不合法的table size
        throw std::invalid_argument("Table size m must be > 0");
    }
    if (str.empty()) {//避免空字串
        throw std::invalid_argument("String size must be > 0");
    }


    unsigned long long hash = 0;
    for(auto i: str){   //直接把每個字元轉數字 加總當作key
        hash = hash +static_cast<int>(i);
    }
    hash = hash * A; //乘以A來達到發散的效果
    return static_cast<int>(hash % static_cast<unsigned long long>(m));  // 安全轉型
}
