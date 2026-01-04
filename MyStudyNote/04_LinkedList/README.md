# Study Note: Linked List

## 1. 什麼是 Linked List（核心定義）

**Linked List（連結串列）是一種由「節點（node）」組成的線性資料結構**。  
節點在記憶體中 **不必連續**，而是透過指標（pointer）彼此連結。

每個節點至少包含：

- `value`：實際儲存的資料
- `next`：指向下一個節點的指標（最後一個節點為 `null`）

```text
[value | next] -> [value | next] -> [value | null]
```


## 2. 從 Array 到 Linked List 的轉換思維

可以將 Linked List 視為：

> Array 的「順序概念」＋「顯式指標」

### 對照理解

| Array | Linked List |
|------|------------|
| 元素在記憶體中連續 | 節點在記憶體中不連續 |
| 下一個元素靠 index 計算（i + 1） | 下一個節點由 `next` 指標決定 |

 Array 用「index計算」連接元素  
 Linked List 用「指標關係」連接節點


## 3. Linked List 的抽象資料型態（ADT）

從 **Abstract Data Type（ADT）** 角度，Linked List 定義的是「可以做哪些操作」，  
而不是節點實際如何配置在記憶體中。

### 常見操作
- **Create**：建立空的 linked list
- **Insert**：插入新節點
- **Delete**：刪除節點
- **Search**：尋找特定值
- **Traverse**：從頭走訪到尾
- **Update**：修改節點中的值


## 4. 記憶體模型與設計取捨

### 為什麼 Linked List 不需要連續記憶體？
- 每個節點獨立配置
- 只要能存 pointer 即可
- 適合記憶體碎片化的環境

### 代價是什麼？
- 無法用 index 直接存取
- 每次操作都要「走指標」

 **Linked List 用「彈性」換取「隨機存取效能」**


## 5. 時間複雜度分析

設節點數為 `n`

### 存取與搜尋
- **Access（by index）**：`O(n)`
- **Search（by value）**：`O(n)`

原因：必須從 `head` 一個一個走到目標節點。

### 插入（Insert）
- **At head**：`O(1)`
- **At tail**
  - 有 tail pointer：`O(1)`
  - 沒有 tail pointer：`O(n)`
- **At position**
  - 找位置：`O(n)`
  - 改指標：`O(1)`

### 刪除（Delete）
- **At head**：`O(1)`
- **已知節點或前一個節點**：`O(1)`
- **By value / position**：`O(n)`（找）＋ `O(1)`（改指標）

 **Linked List 的優勢在「指標重接」，不是「搜尋」**


## 6. 空間複雜度與隱性成本

### 空間使用
- 節點資料：`O(n)`
- 每個節點額外指標：
  - **Singly**：1 個 pointer
  - **Doubly**：2 個 pointer

### 實務影響
- 記憶體 overhead 比 array 大
- Cache locality 較差（節點分散）

 **理論 O(1)，實務可能慢於 array**


## 7. 優點與缺點（設計層次）

### 優點
- 動態大小，無需 resize
- 插入 / 刪除（已知節點）為 `O(1)`
- 不需要連續記憶體
- 適合作為其他結構的基礎

### 缺點
- 無法隨機存取
- 搜尋仍是 `O(n)`
- 額外指標記憶體成本
- 指標操作易出錯（`null`、memory leak）


## 8. Linked List 的常見變形

### Singly Linked List
- 只有 `next`
- 單向走訪
- 結構最簡單

### Doubly Linked List
- `prev` + `next`
- 可雙向走訪
- 插入刪除更方便
- 記憶體成本較高

### Circular Linked List
- `tail.next` 指向 `head`
- 沒有真正的「結尾」
- 常用於循環結構（round-robin）

### Circular Doubly Linked List
- 結合雙向與循環
- 常見於 OS、LRU cache