# Study Note: Array

## 1. 什麼是 Array（核心定義）

**Array（陣列）** 是一段「**連續記憶體空間**」，用來儲存 **相同資料型別** 的元素，  
每個元素可透過 **索引（index）** 在 **O(1)** 時間內直接存取。

### 關鍵特性
- 連續記憶體（Contiguous Memory）
- 固定偏移量計算位址（`base + index × size`）
- 高效隨機存取（Random Access）

**Array 的本質是「空間換時間」的設計**



## 2. Array 作為抽象資料型態（ADT）

從 **ADT（Abstract Data Type）** 角度來看，Array 提供的是一組「**行為介面**」，而非實作細節。

### 支援的基本操作

| Operation | 說明 | Time |
|---------|-----|------|
| Access | 依 index 讀取 | O(1) |
| Update | 依 index 寫入 | O(1) |
| Insert | 插入元素（需位移） | O(n) |
| Delete | 刪除元素（需位移） | O(n) |
| Traversal | 逐一走訪 | O(n) |

**Array 的效能瓶頸幾乎都來自「位移（shift）」**



## 3. 記憶體模型與 Array 的效率來源

### 為什麼 Array 可以 O(1) 存取？

```c
array[i] 位址 = base_address + i * sizeof(type)
```

CPU 可以在常數時間內直接算出位址。

### 為什麼 Insert / Delete 慢？
- 中間插入 → 後面元素必須整體往後搬
- 中間刪除 → 後面元素必須往前補

**Array 的速度優勢，建立在「元素不頻繁移動」之上**



## 4. Static Array（靜態陣列）

### 特性
- 編譯期配置（Compile Time）
- 大小固定，無法變更
- 記憶體通常在 stack 或 static 區段

### 使用時機
- 元素數量已知且固定
- 追求極低 overhead
- 不需要 resize

### 限制
- 無法動態成長
- 容量不足必須整個重建

**Static array = 安全、快，但缺乏彈性**


## 5. Dynamic Array（動態陣列）

### 核心概念
- 透過 `malloc / realloc / free`
- 配置在 heap
- 可在 runtime 調整大小

### Resize 的本質（非常重要）
- 原地擴充（O(1)）
- 重新配置 + 全拷貝（O(n)）

**舊指標可能失效 → 這是 C 語言中常見 bug 來源**



## 6. 成長策略（Amortized Analysis）

```
容量不足時 ×2 擴充
```

- 單次 resize：O(n)
- 平均攤提：`push_back` → **Amortized O(1)**

**這也是 vector、ArrayList 的設計核心**



## 7. 時間與空間複雜度總覽

### Time Complexity

| 操作 | 複雜度 |
|----|------|
| Read / Write | O(1) |
| Traverse | O(n) |
| Search（unsorted） | O(n) |
| Search（sorted） | O(log n) |
| Insert（middle） | O(n) |
| Delete（middle） | O(n) |
| Append（dynamic） | Amortized O(1) |

### Space Complexity
- 元素本身：O(n)
- 額外空間：O(1)
- 動態陣列預留容量：≤ O(n)



## 8. Array 的優缺點（設計層次）

### 優點
- 高速隨機存取
- Cache-friendly（對 CPU 非常友善）
- 記憶體使用效率高
- 結構簡單、易理解

### 缺點
- 中間插入 / 刪除成本高
- Resize 代價大
- C 語言需手動管理記憶體
- 指標失效風險

**Array 是效能導向結構，不是萬用結構**

