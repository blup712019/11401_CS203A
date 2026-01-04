# Study Note: Stack & Queue 

## Overview
Stack（堆疊）與 Queue（佇列）都是用來管理「尚未處理完」的資料/任務的線性資料結構。它們最大的差異在於**取出元素的順序規則**：Stack 是後進先出（LIFO），Queue 是先進先出（FIFO）。

## 1. 比較表

| 結構 | 取出規則 | 插入端 | 刪除端 | 典型比喻 | 最常見用途 |
|---|---|---|---|---|---|
| Stack | LIFO | top | top | 盤子疊疊樂 | DFS、回溯、解析括號、Undo |
| Queue | FIFO | rear | front | 排隊 | BFS、排程、緩衝、Producer-Consumer |

> 由「插入/刪除方向」去連到實作：  
> - Stack：輸入/輸出都在同一端（top）  
> - Queue：輸入在 rear、輸出在 front（兩端）  


## 2. 抽象資料型別 ADT 與不變量

### 2.1 Stack（LIFO）
**ADT 定義**：只暴露一個可操作端 **top**。  
**不變量（Invariant）**：
- `top` 指向「最新插入且尚未移除」的元素
- 對任何元素序列：最後 push 的會最先 pop

**形式化**：
- `push(S, x)` 之後，`peek(S) == x`
- 若 `S` 非空，`pop(S)` 會回傳「最近一次 push 且尚未被 pop」的元素

### 2.2 Queue（FIFO）
**ADT 定義**：兩個端點：  
- **rear**：插入端（enqueue）  
- **front**：移除端（dequeue）

**不變量（Invariant）**：
- 先進入 queue 的元素，一定先被移除
- `front` 永遠指向「最早進入且尚未移除」的元素


## 3. ADT 的具體操作與錯誤條件（Underflow / Overflow）

### 3.1 Stack 常用 API
- `create()`：建立空 stack
- `push(x)`：放入 x
- `pop()`：移除並回傳 top
- `peek()` / `top()`：回傳 top（不移除）
- `isEmpty()`
- `size()`（若維護計數器則 O(1)）

**Underflow**：空 stack 做 `pop/peek`  
**Overflow**：固定大小陣列且已滿時 `push`

### 3.2 Queue 常用 API
- `create()`
- `enqueue(x)`：從 rear 插入
- `dequeue()`：從 front 移除並回傳
- `front()` / `peek()`：看 front
- `isEmpty()`
- `size()`

**Underflow**：空 queue 做 `dequeue/front`  
**Overflow**：固定容量 ring buffer 已滿時 `enqueue`


## 4. 實作：Array vs Linked List

### 4.1 Stack 實作

#### A) Array-based Stack（動態陣列 / vector）
**狀態**：
- `top`（或 `n-1`）  
- `arr`（容量可能大於元素數）

**操作**：
- `push`：`arr[++top] = x`（若滿則擴容）
- `pop`：回傳 `arr[top--]`

**注意**：
- 動態陣列擴容會造成單次 `push` 最壞 O(n)，但攤銷是 O(1)

#### B) Linked-list Stack
**策略**：把 **head 當 top**（最自然）  
- `push`：插到 head  
- `pop`：移除 head  

**優缺**：
- 優：不需要 resize；每次 O(1)  
- 缺：每個節點多指標開銷；快取較不友善



### 4.2 Queue 實作

#### A) Array-based Queue：Circular Buffer / Ring Buffer（重點！）
**為什麼要 circular？**  
如果用一般陣列 queue，`dequeue` 後把元素整個 shift，會變成 O(n)（要避免）。

**狀態**：
- `front`：下一個要取出的索引
- `rear`：下一個要放入的索引（或最後元素的下一格）
- `size`：當前裡面的元素數量
- `cap`：容量

**索引前進**：
- `i = (i + 1) % cap`

**Empty / Full 判定**：
1) **維護 size**
- empty：`size == 0`
- full：`size == cap`

2) **空一格法(避免empty跟full時情況一樣)**
- empty：`front == rear`
- full：`(rear + 1) % cap == front`
- 有效容量少 1（容易忘）

#### B) Linked-list Queue
**策略**：同時維護 `head` 與 `tail`  
- `enqueue`：接在 `tail`  
- `dequeue`：從 `head` 拿  
- 當 dequeue 之後變空：`head = tail = null`（很常漏）


## 5. 複雜度：時間與空間

### 5.1 Stack
| 操作 | Array（動態） | Array（固定） | Linked list |
|---|---:|---:|---:|
| push | 攤銷 O(1)，最壞 O(n) | O(1) 但可能 overflow | O(1) |
| pop | O(1) | O(1) | O(1) |
| peek | O(1) | O(1) | O(1) |
| isEmpty | O(1) | O(1) | O(1) |

### 5.2 Queue
| 操作 | Circular array | Linked list |
|---|---:|---:|
| enqueue | O(1)（固定容量）/ 攤銷 O(1)（可擴容） | O(1)（有 tail） |
| dequeue | O(1) | O(1) |
| front | O(1) | O(1) |

### 5.3 空間
- array：O(C)（容量 C ≥ n）
- linked list：O(n) + 每節點指標額外負擔


## 6. 常見陷阱

### 6.1 Circular Queue 常見坑
- **滿/空判斷搞混**：`front == rear` 到底是空還是滿？  
  - 用 size 最不容易錯
- **rear/front 誰指向元素、誰指向下一格**：定義要一致  
  - 建議：`rear` 指向「下一個可插入位置」
- **mod 忘記**：`(idx + 1) % cap`

### 6.2 Linked list Queue 常見坑
- dequeue 到空時沒有同步清 `tail`
- 釋放節點（C/C++）避免 memory leak

### 6.3 Stack 常見坑
- pop/peek 沒檢查空（underflow）
- 遞迴 DFS 可能造成 call stack overflow（可改顯式 stack）


## 7. 變形與進階結構

### 7.1 Stack 變形
- **Min Stack / Max Stack**：用輔助 stack，讓 `getMin()` O(1)
- **Monotonic Stack**：維持單調性（常解 Next Greater/Smaller Element）
- **Two stacks in one array**：兩端往中間長，共用容量

### 7.2 Queue 變形
- **Deque**：雙端 queue（兩端都能插/刪）
- **Priority Queue**：不是 FIFO，依優先權（通常 heap，O(log n)）
- **Blocking Queue**：多執行緒同步（生產者消費者）
- **Queue via two stacks**：用兩個 stack 模擬 FIFO（攤銷 O(1)）
- **Monotonic Queue**：滑動視窗 min/max（整體 O(n)）