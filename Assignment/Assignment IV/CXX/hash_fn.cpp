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
#define INF 4000000000
int myHashInt(int key, int m) {
    return key % m;  // 線性作法
}

int myHashString(const std::string& str, int m) {
    unsigned long hash = 0;
    for(auto i: str){   //直接把每個字元轉數字 加總當作key
        hash = (hash +(int)i) % INF; //避免整數溢位
    }
    return static_cast<int>(hash % m);  // basic division method
}
