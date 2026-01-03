# Data Structures Quiz Summary README

## Quick Navigation

* [Quiz 1：Introduction to C Programming & Data Structures](Quiz%20I/)
* [Quiz 2：Array, Linked List, Stack and Queue](Quiz%20II/)
* [Quiz 3：Hash Table](Quiz%20III/)
* [Quiz 4：Tree/Heap/Graph(Take-Home)](Quiz%20IV/)
* [Quiz 5： Tree/Heap/Graph](Quiz%20V/)

---

## Quiz 1
這次考試的重點在:
* 聚焦 **C 語言基礎與資料結構核心觀念**，包含動態記憶體配置與管理。
* 熟悉 `malloc`、`realloc`、`free` 的正確使用方式，並理解錯誤用法可能導致的 memory leak 與 undefined behavior。
* 透過 code review 題目培養 **實務導向的 memory safety 思維**，如檢查回傳值與使用暫存指標處理 `realloc`。
* 練習判斷常見操作的 **時間複雜度（Big-O）**，包含 array 存取、搜尋、排序與複雜度排序。


---

## Quiz 2
這次考試的重點在:
* 理解 **基本資料結構的概念與視覺化表示**，包含 Array、Linked List、Stack 與 Queue 的結構差異與操作方向。
* 熟悉 **Linked List 指標操作的實作邏輯**，透過 `MoveTo` 函式練習節點的拆除與重新插入。
* 能辨識並處理 **Linked List 的邊界情況（edge cases）**，如 target 為 head、target 與 destination 相鄰，並理解 dummy node 的用途。
* 清楚定義 **Stack（LIFO）與 Queue（FIFO）**，並掌握其基本操作（push/pop、enqueue/dequeue、front/top）。
* 透過 AI Copilot prompt 題目，了解如何正確使用AI。

---

## Quiz 3
這次考試的重點在:
* 理解 **Hash Table 的核心概念與名詞定義**，包含 collision、bucket、load factor（α）及其對效能的影響。
* 分辨 **不同 collision handling 機制**，特別是 open addressing 與 separate chaining 的結構差異與使用方式。
* 了解 **primary clustering 與 secondary clustering** 的成因，並知道 linear probing 容易產生 primary clustering。
* 練習實際計算 **Hash Function 的結果**，包含 division method（mod）與 folding method，並觀察 collision 產生的模式。
* 比較不同 hash function 的 **key 分布效果**，理解設計良好 hash function 能降低 collision、提升查找效率。

---

## Quiz 4
這次考試的重點在:
* 理解並能描述 **BFS（Breadth-First Search）在 Graph 上的流程**：使用 queue、逐層（level-by-level）拜訪節點，並用 visited 避免重複走訪。
* 能根據圖形給出 **BFS traversal order**，並理解因為同層鄰居的選取順序不同，BFS 可能會出現多種合法走訪序列。
* 熟悉 **Tree traversal 的 inorder traversal**，能用 inorder 由 expression tree 還原算式，並正確計算最終結果。
* 了解 binary tree 的分類方式：能分辨 **shape-based（結構限制）** 與 **criteria-based（規則/排序限制）** 的樹，並舉例說明（如 complete binary tree vs BST/AVL/RB-tree/heap）。

---

## Quiz 5
這次考試的重點在:
* 熟悉 **Tree 與 Graph 的基本定義**，能對照圖示正確辨認 root、degree、height/depth/level、subtree、parent/child/siblings、leaf，以及 graph 的 vertex、edge、weighted edge（cost）。
* 能把「一般樹（general tree）」轉成 **度為二的樹（二元樹）表示法**，核心是 **Left-Child Right-Sibling（LCRS）** 的轉換概念。 
* 掌握 LCRS 的轉換步驟：**first child → left child**、**next sibling → right child**，並移除其他原本的 sibling/child 連結，只保留這兩種指標關係。
* 能看懂並畫出轉換後的 **binary tree 結果**，理解它是在「表示法」上變成 binary tree，而不是改變原本樹的階層/兄弟關係。


