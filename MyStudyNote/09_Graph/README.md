# Study Note: Graph

### Graph 是什麼
- Graph = **Vertices (V)** + **Edges (E)**：用「點」表示實體，用「邊」表示關係。
- 與 Tree 最大差異：Graph 允許 **cycle（環）**、不一定連通、也不一定有 root。

## 正式定義：G = (V, E)
- **Undirected graph**：邊是無序對 `{u, v}`（不分方向）。
- **Directed graph (digraph)**：邊是有序對 `(u, v)`，代表方向 `u → v`，且 `E ⊆ V × V`。

## Graph vs Tree
- Tree：無環、（常假設）連通、階層清楚、兩點間路徑唯一。
- Graph：可能有環、可能不連通、可能有向、甚至允許多重邊或 self-loop。
- 推論：Graph 不能用「父子/唯一通路」直覺寫演算法（可能很多路、也可能繞圈）。

## Adjacency（鄰接）與 Degree（度數）
- 鄰接：
  - 無向：`{u, v} ∈ E` → u 與 v 鄰接
  - 有向：`(u, v) ∈ E` → u 指向 v（out-neighbor）
- 度數：
  - 無向：`deg(v)` = incident 到 v 的邊數
  - 有向：`in-degree`（指向 v 的邊數）、`out-degree`（從 v 指出的邊數）

## Walk / Trail / Path
- **Walk**：可重複頂點、可重複邊，只要相鄰點間有邊即可
- **Trail**：walk 但 **不重複邊**
- **Path**：walk 但 **不重複頂點**（因此也不重複邊）

## Cycle 與圖的類型
- **Cycle**：起點=終點的一種路徑概念（環）
- **Simple graph**：無 self-loop、無多重邊
- **Multigraph**：允許多重邊
- **Pseudograph**：允許 self-loop

## Handshaking Lemma
- `Σ deg(v) = 2|E|`
- 推論：奇數度頂點的數量一定是偶數

# 2. Representation

### 先抓兩個參數
- `n = |V|`（頂點數），`m = |E|`（邊數）
- Dense：`m ≈ n^2`；Sparse：`m << n^2`（現實世界多偏稀疏）
- 表示法選擇會直接改變：空間、查邊、列鄰居、BFS/DFS 的成本

## 1) Adjacency Matrix（鄰接矩陣）
### 定義
- `A[u][v] = 1/weight` 表示有邊（無向則對稱）
- 有向圖：`A[u][v]` 表示 `u → v`

### 優點
- 查邊 `(u,v)`：`O(1)`（最強）
- 實作直覺，適合小圖/稠密圖/大量查邊場景

### 缺點
- 空間：`O(n^2)`（稀疏圖超浪費）
- 列出 u 的鄰居要掃整列：`O(n)`
- BFS/DFS 常變 `O(n^2)`（因為每點掃一整列）

### 什麼時候用
- 圖小或很稠密
- 主要操作是「判斷兩點是否相連」

## 2) Adjacency List（鄰接串列）
### 定義
- `adj[u] = [neighbors...]`（有向圖通常存 out-neighbors）
- 無向圖：一條邊 (u,v) 會出現在 `adj[u]` 與 `adj[v]`

### 優點
- 空間：`O(n + m)`（稀疏圖首選）
- 列鄰居：`O(deg(u))`
- BFS/DFS：`O(n + m)`（幾乎標準）

### 缺點
- 查邊 `(u,v)`：`O(deg(u))`（要在 list 裡找）
  - 可用 `set`/hash 改善，但會增加空間與常數

### 什麼時候用
- 預設首選（大多圖是稀疏）
- 需要大量 traversal、最短路、連通性分析等

## 加權圖怎麼存（weight 放哪）
- Matrix：`A[u][v] = w`，無邊用 `∞/None`
- List：`adj[u]` 存 `(v, w)`
- Edge list：存 `(u, v, w)`

## 操作複雜度對照表
| 操作 | Matrix | List | Edge list |
|---|---:|---:|---:|
| 空間 | `O(n^2)` | `O(n+m)` | `O(m)` |
| 查邊 (u,v) | `O(1)` | `O(deg(u))` | `O(m)` |
| 列鄰居 u | `O(n)` | `O(deg(u))` | `O(m)` |
| 加邊 | `O(1)` | `O(1)` amortized | `O(1)` |
| BFS/DFS | `O(n^2)`* | `O(n+m)` | 不適合直接 |

# 3. Traversal（BFS / DFS )

### 為什麼一定要 `visited`
- Graph 可能有 **cycle**、也可能有多條路到同一點
- 沒有 visited 會：
  - 無限迴圈（尤其 DFS 遞迴）
  - 重複擴展同一點 → 複雜度爆炸
- 走訪不變量：**每個 vertex 最多被正式擴展一次**
- 用 adjacency list 時 → BFS/DFS 總複雜度可達 **O(n+m)**

## BFS（Breadth-First Search）
### 核心特性
- 用 **queue**
- 按層擴展（距離 0,1,2...）
- 在 **無權圖** 產生最短邊數距離（unweighted shortest path）

### BFS 模板（概念）
1. 起點入隊、標 visited、dist[start]=0
2. while queue not empty:
   - u = pop
   - for v in adj[u]:
     - if not visited[v]:
       - visited[v]=true
       - dist[v]=dist[u]+1
       - parent[v]=u
       - push v

### 常見用途
- 無權最短路（最少步數）
- 分層/層數（layering）
- 二分圖檢查（two-color / parity）

## DFS（Depth-First Search）
### 核心特性
- 用 **遞迴** 或 **顯式 stack**
- 先深入到底再回溯
- 適合做結構性分析（會產生探索/完成順序）

### DFS 模板（概念）
`dfs(u): visited[u]=true; for v in adj[u]: if not visited[v]: dfs(v)`

### 常見用途
- 連通分量（connected components）
- cycle detection（無向/有向判法不同）
- Topological sort（DAG）
- SCC、bridge、articulation point（進階）

## Connected Components（圖不一定連通）
- 外層再包一圈：
  - for v in V:
    - if not visited[v]:
      - BFS/DFS(v)
      - component_count++

## Cycle Detection
### 無向圖
- DFS 遇到 `visited[v] == true` 且 `v != parent[u]` → 有 cycle
- 為何排除 parent：無向邊會在兩邊 adjacency 出現，回到 parent 不算 cycle

### 有向圖
- 用三色/recursion stack：
  - 白：未訪問
  - 灰：在遞迴棧上（探索中）
  - 黑：已完成
- 若遇到邊 `u -> v` 且 `v` 是灰色 → back-edge → 有向 cycle

## BFS vs DFS 怎麼選
- 要 **無權最短路 / 按層** → BFS
- 要 **拓撲、cycle、SCC、橋/割點** → DFS
- 工程提醒：
  - DFS 遞迴可能爆棧（深圖）→ 可用迭代 DFS
  - BFS queue 可能很大（寬圖）

## 複雜度總結
- adjacency list：
  - 每點處理一次 → O(n)
  - 每邊掃一次（無向算兩次）→ O(m)
  - **總計 O(n+m)**
- adjacency matrix：
  - 列鄰居要掃整列 O(n)，對每點都掃 → **O(n^2)**

# 4. Pros & Cons

## Pros（優點)

### 1) 最通用的「關係」模型
- Tree 擅長階層；Graph 能表達：
  - 多對多關係（多人互相連結）
  - 循環依賴（cycle）
  - 非連通世界（多個 components）
  - 方向性（A→B 與 B→A 不同）
- 這讓它能自然建模：社交網路、道路網、推薦/連結、依賴圖、狀態轉移圖。

### 2) 能把「局部連結」推導成「全域性質」
- 從 adjacency（鄰接）可以推導：
  - 連通性/可達性（能不能到）
  - 群聚/社群結構（哪些點常在一起）
  - 依賴關係（先後、影響鏈）
- 這是 Graph 的超能力：**局部邊 → 全域結構**。

### 3) 表示法彈性高，能依資料特性選擇最合適的儲存
- 稀疏圖：adjacency list 省空間又快（O(n+m) 思維）
- 稠密圖：adjacency matrix 查邊 O(1) 很香
- 邊導向任務：edge list 非常直覺
- 同一個問題可以用不同 representation 做不同 trade-off（空間 vs 查詢速度）。

### 4) 能統一很多「看起來不同」的問題
- 許多問題本質是：
  - 「狀態」= vertex
  - 「可轉移」= edge
- 例如迷宮、棋盤、字典變換、流程/依賴，都可以被統一成「可達性」或「路徑」類問題。

### 5) 可擴充性好：權重、多重邊、屬性都能自然附加
- Edge 上可以放權重（成本/距離/機率）
- Node 上可以放標籤/類別/容量
- 同一張圖可以承載多層語意（多種關係、不同 type 的邊）
- 很容易與資料工程/ML 特徵結合（例如 graph embeddings 的直覺基礎）。

## Cons（缺點/風險）

### 1) 建模成本高：你先把問題「畫錯圖」就全盤皆錯
- 常見建模雷點：
  - 邊方向搞反（dependency 的方向很常被畫反）
  - 權重定義錯（成本/收益/機率混用）
  - 把「需要多層狀態」硬塞成單一節點（導致漏掉條件）
- Graph 很強，但前提是你用對抽象：**錯誤建模比錯誤程式更難抓**。

### 2) Cycle 與多路徑讓推理變複雜（不像 tree 有唯一通路）
- 在 tree 中兩點間路徑唯一，很多證明/推理很簡單
- 在 graph 中可能：
  - 很多條路、互相繞圈
  - 局部改動會造成全局影響（尤其有向圖）
- 你幾乎總需要 `visited / 狀態標記` 才能避免重複與無限循環。

### 3) 複雜度容易爆炸：n、m 都可能很大
- Graph 的成本通常跟 `n+m` 或 `n^2`、`n*m` 這類量綁在一起
- 一旦圖很大：
  - adjacency matrix 直接空間爆炸（O(n^2)）
  - 全點對性質常變得不可能（例如 O(n^3) 類）
- 所以圖題很重要的一步是：**先判斷稀疏/稠密、先選 representation**。

### 4) 資料品質敏感：噪音邊、缺邊都可能扭曲結構
- 真實資料常有：
  - 假連結（noise edges）
  - 漏連結（missing edges）
  - 動態變化（edge/vertex 時間漂移）
- 這會讓「結構性結論」不穩，尤其在社交/推薦類圖上更明顯。

### 5) 工程實作要點多：方向、權重、邊界條件、記憶體佈局
- 同一個圖題，錯誤最常出在：
  - 有向/無向處理不一致（無向忘了加反向邊）
  - 自環/多重邊處理（是否要去重、是否要累加）
  - visited/parent/距離初始化
  - 大圖記憶體（list of lists vs vector、壓縮存法）
- 這些不是「演算法」本身，但會決定你是否能跑出正確且高效的結果。

## 總結
- **Graph = 最通用的關係語言**（能表達世界的「網狀結構」）
- **代價 = 推理與工程複雜度上升**（cycle、多路徑、表示法選型與資料品質）