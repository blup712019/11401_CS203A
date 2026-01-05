# Study Note: Heap
# 1. 核心概念

### Heap 是什麼（Binary Heap）
- Heap = **Complete Binary Tree** + **Heap-order property**，通常用 **array** 存。
- Max-heap：parent ≥ children → **最大值在 root**
- Min-heap：parent ≤ children → **最小值在 root**

## 不變量 1：Shape Property（為什麼要 Complete）
- Complete：除最後一層外全滿，最後一層由左到右填。
- 好處：
  - 樹高 `h = O(log n)` → 上下調整（sift）成本可控
  - 可用陣列緊密存（無洞）→ cache 佳、少指標開銷

## 不變量 2：Heap Property（保證 vs 不保證）
### 保證
- root 永遠是極值（min/max）
- `Peek()` 直接看 root → `O(1)`

### 不保證
- **不是全域排序**（inorder/任何走訪不等於排序）
- 沒有 BST 那種「左全小右全大」
- 搜尋任意 key 通常接近 `O(n)`（沒有全域 order）

## Array 表示法（0-indexed）
- `parent(i) = (i - 1) // 2`
- `left(i)   = 2i + 1`
- `right(i)  = 2i + 2`
- 核心操作（插入上浮、刪根下沉、build-heap）都靠這些 index 跳轉 + swap

# 2. ADT 與核心操作

### Heap 操作概念
- Heap 兩個不變量：
  - **Shape（complete）**：靠「插入放最後、刪 root 用最後補上」維持
  - **Order（heap property）**：靠局部交換修復
- 修復：
  - **Sift Up（上浮）**：節點太大(max) / 太小(min) → 往上交換
  - **Sift Down（下沉）**：節點太小(max) / 太大(min) → 往下交換

## ADT 操作與複雜度

### 1) `Peek()`：看極值不移除
- 直接回傳 `A[0]`（root）
- Time：`O(1)`
- 空 heap 要定義行為

### 2) `Insert(x)`：放最後 + 上浮
- 步驟：
  1. `A.append(x)`（維持 complete）
  2. `siftUp(i=last)`：與 parent 比，違反就 swap，直到合法或到 root
- Time：`O(log n)`（最多上浮樹高）

### 3) `ExtractMin/Max()`：拿 root + 最後補上 + 下沉
- 步驟：
  1. 取出 `A[0]`
  2. `A[0] = A[last]`，刪掉 last（維持 complete）
  3. `siftDown(0)`：與「更該在上面」的孩子交換（max: 選較大子；min: 選較小子）
- Time：`O(log n)`

### 4) `Heapify(i)`（局部修復）
- 假設左右子樹已是 heap，把 `i` 當 root 做 **siftDown** 修成 heap
- Time：`O(log n)`
- 是 Extract 與 BuildHeap 的基礎零件

### 5) `BuildHeap(array)`：Bottom-up 建堆
- 做法：從最後一個非葉節點 `i=(n-2)//2` 往回到 `0`，逐個 `heapify(i)`
- Time：`O(n)`（不是 `O(n log n)`）
  - 直覺：越多節點在底層、可下沉高度越小 → 分層加總收斂到 `O(n)`

### 6) `IncreaseKey / DecreaseKey(i, newKey)`：改 key 後往哪走？
- Max-heap：
  - IncreaseKey（變大）→ **siftUp**
  - DecreaseKey（變小）→ **siftDown**
- Min-heap：相反
- 口訣：往「違反方向」修（更該在上就上浮；更該在下就下沉）
- Time：`O(log n)`

### 7) `Delete(i)`：刪任意 index
- 常見做法：
  1. 用 last 覆蓋/交換到 i
  2. size - 1
  3. 依狀況 `siftUp` 或 `siftDown`（通常先跟 parent 比一次決定方向）
- Time：`O(log n)`（但若沒 index，先找元素會是 `O(n)`）

# 3. Pros & Cons
## 3.1 Pros（優點）

### 1) 極值存取便宜：Peek O(1)，抽取 O(log n)
- Root 永遠是 min/max，所以 peek 只要看 `A[0]`；抽取再用 sift 修回來。
**延伸理解：**
- 「O(1) 拿極值」是 heap 的核心賣點：你不需要排序整個集合，就能持續拿到下一個最重要的元素。

### 2) 插入快
- Insert 只要 append 到尾端維持 complete，再 sift-up 修局部順序，成本 O(log n)。
**延伸理解：**
- 當資料是「邊來邊處理」（例如排程、事件模擬、即時 top-k），heap 可以在不全排序的情況下維持「目前最重要者」。

### 3) 空間效率高、cache 友善（array layout）
- Heap 通常用陣列緊密儲存，O(n) 空間且 locality 好。  
**延伸理解：**
- pointer-based tree 的節點分散、cache miss 多；binary heap 的連續陣列在實務上往往跑得很快（常數因子很香）。

### 4) 很適合：Priority Queue / 排程 / 模擬 / top-k / k-way merge
- 對「一直要拿下一個最小/最大」的流程非常自然。 
**常見場景（你可以背成模板）**
- **Top-k（維持 k 個最重要）**：用大小為 k 的 min-heap（保留最大 k 個）或 max-heap（保留最小 k 個）
- **合併多個已排序序列（k-way merge）**：heap 裝每個序列目前的頭 → 每次取最小再推進
- **事件模擬（event simulation）**：下一個事件時間最小，heap 很直覺

### 5) Heapsort：O(n log n) 且可 in-place（額外空間 O(1)）
- heap sort 時間 O(n log n)，可原地排序（額外空間 O(1)）。 
**延伸理解：**
- Heapsort 的優點是「空間很省」+「最壞情況也有保證」；缺點是不穩定且常數未必最漂亮。

## 3.2 Cons（缺點）

### 1) 找任意 key 慢：通常 O(n)
- Heap 只有父子局部有序，沒有 BST 那種全域 order，所以「找某個值在哪」沒有捷徑。
**延伸理解：**
- 這也是為什麼 heap 不適合當作「dictionary / set」的底層；它是 priority 的工具，不是查找表。

### 2) 有序操作弱：range / predecessor / sorted iteration 很不友善
- 想要「比 x 小的最大值」或「區間 [L, R]」這種操作，heap 沒有天然結構支援。
**延伸理解：**
- 需要「順序語意」時，balanced BST / B-tree 家族更合理。

### 3) DecreaseKey / Delete 常需要額外索引（index map / handle）
- heap 要更新某個元素，通常得先知道它的 index；否則先找它就 O(n)。實務常加一個 map 來追蹤 value→index。

### 4) Heapsort 不穩定（stability）
- heapsort 預設不穩定：相等 key 的相對順序可能改變。

### 5) 常數因子不一定贏：某些狀況下 BST / specialized queue 可能更好
- 在某些工作負載下，儘管 big-O 類似，平衡樹或特化隊列可能更快。

# 4. Variations
- 變形的核心：**改變「分支度 / 結構」或加入額外不變量，來強化某些操作（尤其 merge、decrease-key、雙端極值等）**

## 4.1 Binary Heap（標準二元堆）
- Complete binary tree + heap-order，通常 array 存。 
- 強項：peek、insert、extract（對 priority queue 很夠用）
- 弱項：merge（meld）通常不快；decrease-key 若沒有 handle 會麻煩
## 4.2 d-ary Heap（多叉堆）
- 每節點最多 d 個孩子（例如 4-ary heap）。
- 增加分支度 → **降低高度**（高度約變成 log_d(n)），某些情況能讓 decrease-key（上浮）更快。
**代價 / 取捨**
- 下沉時要在 d 個孩子中找「最該交換的那個」→ 每層比較變多  

## 4.3 Meldable Heaps（可合併堆）：把 merge 做快
很多變形的重點在 **merge/union（meld）**：把兩個 heap 合成一個 heap。

### Binomial Heap（雙項堆）
- 由多棵 binomial trees 組成，支援 efficient merge（union）。:contentReference[oaicite:14]{index=14}  
**直覺**
- merge 像二進位加法：同階樹合併成更高一階

### Fibonacci Heap（費波那契堆）
- 進階 meldable heap，強調 amortized 操作（特別是 decrease-key 很快），常出現在理論分析（例如 Dijkstra）
**直覺**
- 用「延遲整理（lazy）」把成本攤提到後面，換到超快的 amortized decrease-key

### Pairing Heap（配對堆）
- 更簡單、實作相對友善，常被視為 Fibonacci heap 的實務替代品。

### Leftist Heap（左偏堆）
- 維持「null-path length」性質，讓合併時樹保持偏斜以利 merge。 

### Skew Heap（斜堆）
- 自我調整（self-adjusting）meldable heap，merge 很簡單，不需額外平衡資訊。
