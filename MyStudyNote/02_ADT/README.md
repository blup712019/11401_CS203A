# Study Note: Abstract Data Type (ADT)

**ADT（Abstract Data Type）** 是電腦科學中的一個基本概念。它們僅從行為的角度來定義資料結構，著重於所支援的操作以及這些操作的使用規則，而不是其實作細節。



## 1. DS vs ADT：先講清楚「是什麼」與「能做什麼」

- **資料結構（Data Structure, DS）**：偏向「怎麼存、怎麼連、怎麼實作」  
  例：用陣列或鏈結串列實作 queue，記憶體配置、擴容策略、指標管理都不同。
- **抽象資料型別（ADT）**：偏向「行為與規則」，定義你能做的操作與使用限制，而不關心怎麼做  
  例：Queue ADT 只規定 FIFO 行為與操作（enqueue/dequeue/front…），實作可替換。




## 2. 如何把一個 ADT 寫「完整」？

一個好用的 ADT 規格通常包含：

1. **抽象模型（Model）**  
   - Stack：一個序列，符合 LIFO  
   - Set：不重複元素的集合
2. **操作集合（Operations）**  
   - 例如 Stack：`push(x) / pop() / top() / isEmpty() / size()`
3. **前置/後置條件（Pre/Post conditions）**  
   - `pop()` 前置：stack 非空  
   - `push(x)` 後置：`top()==x` 且 `size+1`
4. **不變量（Invariants）**：結構必須永遠成立的規則  
   - BST：左 < 根 < 右  
   - Heap：父節點優先級 ≥ 子節點  
   - Graph：是否允許環、是否連通等
5. **錯誤語意（Error semantics）**  
   - 空 `pop()`：丟例外？回傳特殊值？



## 3. 常見 ADT 範例（只看介面與規則）
### 3.1 Stack ADT（LIFO）
- 操作：`push`, `pop`, `top`, `isEmpty`, `size`
- 規則：最後放入者最先被取出

### 3.2 Queue ADT（FIFO）
- 操作：`enqueue`, `dequeue`, `front`, `isEmpty`, `size`
- 規則：最早放入者最先被取出

### 3.3 Set ADT（不重複集合）
- 操作：`add`, `remove`, `contains`, `size`
- 規則：元素不重複；`add(x)` 後 `contains(x)=true`

### 3.4 Map/Dictionary ADT（Key → Value）
- 操作：`put(k,v)`, `get(k)`, `remove(k)`, `containsKey(k)`
- 規則：key 唯一；`put` 可能覆蓋舊值

### 3.5 Priority Queue ADT（依優先度取出）
- 操作：`insert`, `top`, `popTop`
- 規則：每次取出的都是最高/最低優先度元素（依定義）



## 4. 為什麼 ADT 很重要？
- **分離介面與實作**：使用者只依賴 ADT，不被特定資料結構綁死
- **更容易替換/優化**：需求不變時，可換 DS 以改善效能
- **更好溝通與設計**：先把行為說清楚，再談實作細節