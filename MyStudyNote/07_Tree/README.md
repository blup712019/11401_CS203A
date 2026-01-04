# Study Note: Tree

# 1. Tree的核心概念與術語

### Tree 是什麼
- Tree（樹）是**階層式（hierarchical）**、**非線性**資料結構。
- 圖論視角：
  - 無向樹：**connected + acyclic**
  - 有根樹（常見實作）：指定 **root**，形成父子階層。

## 三個關鍵定義
- 任意兩點間有且只有一條簡單路徑（unique path）
- 若有 `n` 個節點，必有 `n - 1` 條邊
- 任意移除一條邊都會斷開（每條邊都是 bridge）

## 基本術語（rooted tree）
- Root：根（入口）
- Parent / Child：父/子（直接上下）
- Siblings：兄弟（同父）
- Leaf：葉節點（沒有 child）
- Internal node：內部節點（至少 1 child）
- Ancestor / Descendant：祖先/後代
- Subtree：某節點 + 所有後代
- Forest：多棵樹的集合（移除 root 後常形成 forest）

## Depth / Height（常混淆）
- Depth(node)：root 到該節點的邊數（root depth = 0）
- Height(node)：該節點到最深 leaf 的最長路徑邊數
- Tree height：root 的 height

## 分支度(Degree)與分類
- Degree：某節點 children 數
- k-ary tree：每節點最多 k 個 children（binary tree = 2）
- Ordered vs Unordered：
  - ordered：children 有順序（如BST）
  - unordered：children 無順序（如組織圖）

# 2. 從 Linked List 到 Tree：指標如何長成階層

### 從線性到分岔
- Linked List：每個節點只有一個 `next` → 結構是線性的（每步只有 1 條路）
- Tree：每個節點可有 `0..k` 個 children pointers → 會分岔形成階層
- Binary tree：一般樹的特例（最多 2 個 children）

## 為什麼需要 root 與「唯一 parent」
- Root：整棵樹的入口
- 除 root 外，每個節點 **恰好一個 parent**
  - 保證從 root 可達整棵樹（traversal/搜尋才有定義）
  - 保證從任一節點回 root 的路徑唯一（depth/ancestor/LCA 更好處理）

## Tree 節點資料模型（怎麼存 children）
- General tree：`children` 用 list/array/vector（彈性、直觀）
- Binary tree：固定 `left/right`（經典 traversal 有漂亮性質）
- 選配 `parent` 指標：方便往上爬，但多一個指標且維護更麻煩

## 三種常見表示法（記憶體模型的選擇）
1) Pointer-based（指標樹）
- 最通用（BST/AVL/RB tree 常用）
- 優：形狀任意、操作彈性
- 缺：指標/配置成本、cache locality 較差

2) Array-based（陣列樹）
- 適合 complete tree（heap 最常見）
- 1-indexed：left=`2i`, right=`2i+1`
- 0-indexed：left=`2i+1`, right=`2i+2`, parent=`(i-1)//2`
- 優：連續記憶體、cache 佳
- 缺：稀疏樹會浪費空間

3) Left-Child Right-Sibling（LCRS）
- 用二元樹指標表示一般樹
- `left` = 第一個孩子；`right` = 下一個兄弟
- 優：每節點固定兩指標也能表示多叉
- 缺：語意較不直觀，需要轉換思維

## 核心觀念
- Tree 的難點來自「分岔」→ 需要走訪策略（DFS/BFS、pre/in/post/level）
- 子樹（subtree）讓很多問題能局部解（分治/遞迴自然出現）

# 3. ADT (以Binary Tree來考量)


### ADT 的意義
- ADT（Abstract Data Type）先定義「能做什麼操作 + 語意」，暫時不管底層怎麼存，這邊先以Binary Tree來考量。

## Binary Tree ADT：最小但完整的必要操作
- `Create()`：建立空樹
- `IsEmpty(bt)`：是否為空
- `MakeBT(bt1, item, bt2)`：用「左子樹 bt1 + 根 item + 右子樹 bt2」組成新樹
- `Lchild(bt)`：取左子樹
- `Rchild(bt)`：取右子樹
- `Data(bt)`：取根資料

> 這組操作對應遞迴定義：Tree = (Left, Root, Right)，足以表達大多數樹演算法。


## 操作語意與常見陷阱
### `Create()`
- 回傳 empty tree（指標實作常是 `NULL` / `nullptr`）
- 通常 `O(1)`

### `IsEmpty(bt)`
- 判斷是否空樹（多數操作的安全前置檢查）
- 通常 `O(1)`

### `Data(bt)`
- 取 root 的資料
- 前置：`bt` 不能是 empty（否則需定義：exception / sentinel / 要求先 IsEmpty）

### `Lchild(bt)` / `Rchild(bt)`
- 回傳左/右子樹
- 常見語意：**回傳 reference/指標（共享子樹）** → `O(1)`，但有 aliasing（多個變數指到同一子樹）
- 深拷貝語意成本高，實務較少這樣設計

### `MakeBT(bt1, item, bt2)`
- 建立新樹：root=item，left=bt1，right=bt2
- 設計要點：是否允許共享 bt1/bt2（多數 ADT 默認可共享；否則要複製，昂貴）


## 用 ADT 角度理解 traversal
- DFS 三序（pre/in/post）的差別只是 **Data(root) 的時機**：
  - Preorder：`Data → Lchild → Rchild`
  - Inorder：`Lchild → Data → Rchild`
  - Postorder：`Lchild → Rchild → Data`
- 也就是：traversal 是用 `Data/Lchild/Rchild` 排列組合出的訪問規則。


## ADT 與實作的對應（同介面，不同 representation）
- Pointer-based：`Data/Lchild/Rchild` 直接讀節點欄位；形狀任意但指標/配置成本較高
- Array-based（complete tree/heap）：`Lchild/Rchild` 變成 index 計算；cache 佳但稀疏浪費空間、結構調整不彈性
- LCRS：用 `left=第一個孩子, right=下一個兄弟` 表示一般樹，讓多叉樹也能轉為二元樹

# 4. Complexity

- 多數樹操作的成本其實是 `O(h)`（h = 樹高 height）
- 所以「快不快」取決於樹的形狀（平衡 vs 不平衡）

## BST 的時間複雜度：平衡 vs 不平衡
### Balanced BST（理想）
- Search / Insert / Delete：`O(log n)`
- 直覺：每往下一層，可能範圍大致折半 → 需要走約 `log2(n)` 層

### Unbalanced（最壞）
- Search / Insert / Delete：`O(n)`
- 直覺：樹退化成 linked list，`h ≈ n`（例如插入已排序資料到普通 BST）

## Traversal（遍歷）
- 時間：四種 traversal（pre/in/post/level）都會拜訪每節點一次 → `O(n)`
- 空間：
  - DFS 遞迴：`O(h)`（recursion stack）
  - BFS level-order：`O(w)`（queue；w = 最大層寬）
- 提醒：樹很深/很不平衡時，遞迴可能 stack overflow → 可改迭代 DFS（顯式 stack）

## 空間複雜度（representation 影響）
### Pointer-based
- 空間：`O(n)`（n 個節點就需要 n 個 node）
- 實務：有 per-node overhead（指標、配置碎片、cache locality 可能較差）

### Array-based（complete tree/heap 常用）
- 空間：約 `O(capacity)`；若樹很稀疏會浪費大量空間
- 直覺：
  - complete tree → array 很香（連續記憶體、cache 佳）
  - sparse / skewed tree → array 很浪費（洞也要占位）

# 5. Pros & Cons

- Tree 的強項在「階層 + 局部性 + 有序性（若選對變形）」；弱點多半在「形狀決定效能 + 工程成本（指標/重平衡/遞迴深度）」。

## Pros（優點）— 樹為什麼值得用

### 1) 天然對應階層（Hierarchy is the data）
- Tree 的 parent→child 關係就是階層語意本身：檔案系統、DOM、組織圖、語法樹(AST)、決策樹、分類樹。
- 用 array/list 也能存階層，但得額外維護：
  - parent/child 關係
  - 子集合範圍（subtree boundary）
  - 更新時的一致性（插入/刪除節點會影響哪些索引）
- Tree 讓「結構」與「資料」一致，建模成本更低、語意更清晰。

### 2) 有序操作很強：支援排序與範圍查詢（Range queries）
- 平衡 BST 能在 `O(log n)` 做：
  - search/insert/delete
  - min/max、predecessor/successor
  - range query（找 [L, R] 之間的所有 key）
- 這是 hash table 做不到的：hash table 沒有順序語意，範圍查詢通常會退化成掃全表。
- 實務例：
  - 需要「查詢最近的一個小於 x 的值」→ balanced BST 很自然；hash table 很彆扭。

### 3) 子樹局部性：把全域問題拆成局部子問題（Divide & Conquer / DP）
- Tree 的遞迴定義讓大量問題有「天然分治結構」：
  - size/height/sum、最大路徑、是否平衡、LCA、tree DP 等
- 很多演算法骨架都是：
  1) 解左子樹
  2) 解右子樹
  3) 合併結果回根（combine）
- 這種局部性也讓「更新或查詢」常能侷限在某條 root→leaf 路徑上（`O(h)`）。

### 4) Traversal 提供多視角輸出與處理模式
- Preorder：先宣告 root → 常用於複製/序列化骨架/分治框架
- Inorder：BST 會輸出排序結果 → 很多「需要排序輸出」的應用直接受益
- Postorder：先子後根 → 很適合釋放資源、由下往上彙總（tree DP）
- Level-order：按層處理 → 常用於序列化、逐層分析、最短層數等

### 5) 樹家族變形多：其實在選「對問題友善的約束」
- Heap：強化「取極值」→ priority queue
- Trie：強化「字首共享」→ prefix 查詢/字典
- B-tree / B+ tree：強化「磁碟 I/O 效率」→ DB / filesystem index
- Segment tree / Fenwick tree：強化「區間查詢與更新」→ range sum/min/max
- 這些變形代表：當問題具有階層、分割、區間、字首等結構時，Tree 往往是最合適的抽象。

## Cons（缺點/風險）— 樹的問題幾乎都在「形狀」與「工程成本」上

### 1) 形狀決定效能：退化時像 linked list（最常見大坑）
- 很多操作成本是 `O(h)`（h = height）
- 若樹平衡：`h ≈ log n` → 很快
- 若樹歪斜：`h ≈ n` → 直接退化成 `O(n)`
- 典型踩雷：普通 BST 插入已排序資料 → 全長在一側。

### 2) 自平衡帶來的工程複雜度（用穩定上界換成本）
- AVL / Red-Black 用旋轉維持平衡，保證 `O(log n)` 上界
- 代價：
  - 實作與除錯複雜（旋轉、顏色/平衡因子維護）
  - 更新操作常數因子變大
- 核心 trade-off：**穩定的 worst-case vs 較高的維護成本**。

### 3) 記憶體與效能常數：指標 + metadata + cache locality
- 指標樹每節點至少：
  - `data` + `left/right`（或 children list）
  - 可能還有 `parent`、平衡因子、顏色、子樹大小等
- 指標分散 → cache locality 差，實際效能可能輸給連續陣列結構（例如 heap、open addressing hash）。
- 所以「Big-O 一樣」不代表實務一樣快：常數因子與 cache 行為常是勝負手。

### 4) 遞迴深度風險：深樹容易 stack overflow
- DFS/traversal/遞迴 DP 常用 recursion
- 深度接近 n 時（歪斜樹）容易爆棧
- 解法：改迭代版（顯式 stack）或用尾端安全策略（視語言而定）。

### 5) 選錯表示法/變形 = 時間或空間災難
- 稀疏樹用 array-based（complete-tree index）→ 空間爆炸
- 大量 range query 卻用 hash table → 常退化掃全表
- 需要穩定 worst-case 卻用普通 BST → 尾延遲不穩（P95/P99 易飆）
- 需要磁碟索引卻用 pointer BST → I/O 次數多、效能差（B-tree 家族更適合）

# 6. Variations
- 每種樹都是在「加上一個或多個不變量（invariant）」來換取某類操作更快/更穩。

## 1) General Tree（k-ary / Multiway Tree）
### 不變量 / 結構特徵
- 每個節點可有 `0..k` 個 children（不限制 2 個）。
- 重點是「父子階層」，不一定有「左右」語意（有序或無序視資料而定）。

### 中藥表示法：LCRS（Left-Child Right-Sibling）
- `left`：指向**第一個孩子**
- `right`：指向**下一個兄弟**
- 優點：用固定兩指標就能表達任意多叉；也能套用「二元樹」的 traversal 工具。
- 缺點：語意不如 `children[]` 直覺；要做「找第 k 個孩子」需沿 sibling 走一段。

### 常見用途
- 檔案系統、DOM、組織架構、分類樹、語法樹（AST）的自然形狀。

## 2) Binary Tree（二元樹）與形狀分類（Full / Perfect / Complete）
### 不變量 / 結構特徵
- 每節點最多兩個孩子：`left/right`。
- 二元樹本身不一定「有序」，只是提供左右分岔骨架。

### 三種重要的形狀
- **Full**：每個 internal node 恰有 2 個孩子（0 或 2，不會只有 1 個）
- **Perfect**：internal 都有 2 個孩子，且所有 leaf 同一層（完全滿）
- **Complete**：除最後一層外都滿；最後一層「由左到右填」

### 為什麼 Complete 特別重要？
- 因為它幾乎等價於「可用 array 高效存」：
  - 0-indexed：left=`2i+1`, right=`2i+2`, parent=`(i-1)//2`
- 這就是 heap 能用陣列超快的底層原因（快取友善、指標開銷低）。

## 3) BST（Binary Search Tree）
### 核心不變量（Ordering Property）
- `left subtree < root < right subtree`  
- 這個不變量把「二元樹」變成「有序集合」：能做排序、範圍查詢框架、前驅/後繼等。

### 典型操作（本質上都是沿 root→leaf 走）
- search / insert / delete：成本約 `O(h)`（h = height）
- inorder traversal：會輸出 **sorted order**（只對 BST 成立）

### 主要風險（BST 最大坑）
- 若不平衡：`h ≈ n` → 退化成 linked list → 操作變 `O(n)`
- 典型踩雷：用「普通 BST」插入已排序資料。


## 4) Self-Balancing BST（AVL / Red–Black）
- 目標：用 rotations 維持 `h = O(log n)`，把 worst-case 從 `O(n)` 拉回穩定 `O(log n)`。

### AVL Tree（更「緊」的平衡）
- 不變量（直覺版）：左右子樹高度差限制在小範圍（常見 balance factor -1/0/+1）。
- 特性：
  - 查詢通常更快（樹更矮、路徑更短）
  - 更新（插入/刪除）可能觸發較多旋轉（維護成本偏高）

### Red–Black Tree（更「鬆」的平衡）
- 不變量（直覺版）：允許更鬆的高度界，但保證整體仍是 `O(log n)`。
- 特性：
  - 更新時旋轉通常較少、工程上常用（許多語言標準庫的 map/set 類）
  - 查詢高度可能略高於 AVL（但仍是 log 等級）

## 5) Heap（Priority Queue Tree）
### 核心不變量（Heap-order property + Complete）
- 形狀通常是 **Complete binary tree**
- 次序只保證「父子」：
  - Min-heap：parent ≤ children（根最小）
  - Max-heap：parent ≥ children（根最大）

### 它擅長什麼、不擅長什麼
- 擅長：
  - peek min/max：`O(1)`
  - insert / delete-root：`O(log n)`
- 不擅長（常見誤用）：
  - **heap 不提供全域排序**（只保證根是極值）
  - 要做 range query 或找任意 key 不是 heap 強項

## 6) B-Tree / B+ Tree（外部記憶體友善的平衡搜尋樹）
- 關鍵：在 DB/磁碟世界，瓶頸是 I/O 次數，不是 CPU 比較次數。

### 核心不變量：高分支 + 平衡高度
- 每個節點可放「很多 keys 與 children」（多路搜尋）
- 分支度高 ⇒ 樹高很低 ⇒ 查找只需要很少次「讀頁面」

### B-Tree vs B+ Tree
- **B-Tree**
  - keys 可以存在 internal nodes（不只 leaves）
  - 查找可能在中間層就結束
- **B+ Tree**
  - records/keys 主要集中在 leaves
  - leaves 常串成 linked list ⇒ **range scan 特別快**

## 7) Trie（Prefix Tree）與 Compressed Trie / Radix Tree
### 核心不變量：把字串拆成字元路徑
- 每個節點代表一個 prefix（或一個字元位置）
- 查找/插入/刪除成本通常是 `O(L)`（L = 字串長度），與 key 數量關聯較小

### Trie 的強項
- prefix query 超自然：
  - autocomplete、字典查詢、路由前綴（如 IP 前綴概念）
- 不需要像 BST 那樣靠比較整個字串來決定方向（比較成本被「逐字元」分攤）

### Trie 的主要代價
- 空間可能很大（特別是字元集大、分支稀疏）
- 常見優化：
  - **Compressed Trie / Radix Tree**：把「只有一個孩子」的長鏈壓縮成一條邊（邊上存字串片段）
  - 能顯著減少節點數、提升 cache 行為

## 8) Segment Tree（線段樹）& Fenwick Tree / BIT（樹狀陣列）
- 這兩個常被放在一起比較：都能做 `O(log n)` 的查詢/更新，但**定位與取捨不同**。

### 8.1 Segment Tree（線段樹）
- 目的：支援「區間查詢 + 更新」
  - query：sum/min/max/gcd…（取決於合併操作）
  - update：點更新、甚至可擴充到區間更新（lazy propagation）
- 常見複雜度：
  - query：`O(log n)`
  - update：`O(log n)`
- 核心思想：
  - 把區間切成子區間（左右子樹）
  - 查詢時用少量節點覆蓋目標區間（利用子樹局部性）

### 8.2 Fenwick Tree / BIT（樹狀陣列）
- 目的：更緊湊地支援「點更新 + 前綴查詢（prefix query）」  
- 常見複雜度：
  - point update：`O(log n)`
  - prefix sum/query：`O(log n)`
- 優點：
  - 實作短、常數小、空間 `O(n)` 且結構緊湊（cache-friendly）

## 9) k-d Tree / Quadtree（空間分割樹）
### 9.1 k-d Tree（k-dimensional）
- 目的：在 k 維空間做 range search、nearest neighbor
- 直覺：輪流用不同維度切分空間，形成遞迴分割

### 9.2 Quadtree（2D 常見）
- 目的：把 2D 空間遞迴切成四格（象限）
- 常用在：地圖瓦片、碰撞檢測、影像/空間索引、稀疏空間表示
- 優勢：能快速排除大量不相關區域（剪枝）
