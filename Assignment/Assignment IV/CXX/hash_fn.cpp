/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/23: Initialization
    - 2025/11/23: Added string-hash implementation

   Developer: YI-FENG HUANG <s1123301@mail.yzu.edu.tw>
 */
#include "hash_fn.hpp"
#include <stdexcept>
#define INF 4000000000
int myHashInt(int key, int m) {
    if (m <= 0) { //避免不合法的table size
    throw std::invalid_argument("Table size m must be > 0");
}

    unsigned long hash = (key*key) % INF;
    return hash % m;  // 將key^2 取餘得到位置
}

int myHashString(const std::string& str, int m) {
    if (m <= 0) {//避免不合法的table size
    throw std::invalid_argument("Table size m must be > 0");
}
    if (str.empty()) {//避免空字串
    throw std::invalid_argument("String size must be > 0");
}


    unsigned long hash = 0;
    for(auto i: str){   //直接把每個字元轉數字 加總當作key
        hash = (hash +(int)i) % INF; //避免整數溢位
    }
    hash = (hash*hash) % INF;
    return static_cast<int>(hash % m);  // 將key^2 取餘得到位置
}
