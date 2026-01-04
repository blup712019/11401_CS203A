# Study Note: Hash Table

# 1. 核心概念
- **Hash Table**：用 `hash(key)` 把 key 映射到陣列索引，做 **Key-Value** 的快速查找（Map/Dictionary）。
- 主要組件：
  - 底層陣列 `table[0..m-1]`
  - Hash function：`index = h(key) mod m`
  - 碰撞處理（collision resolution）
  - 負載控制（load factor + resize/rehash）

### 為什麼「看起來像 O(1)」
- 常見說法是操作 **期望 O(1)**，但前提是：
  - hash 分佈要夠平均（別集中到少數桶）
  - **load factor** 不要失控

### Load Factor（負載因子）
- 定義：`α = n / m`
  - `n`：元素數量
  - `m`：桶/槽數量
- 直覺：平均每個桶/槽有多「擠」

### 更精準的成本模型
- **Separate Chaining（拉鍊法）**：
  - 每個 bucket 放一個小容器（list/array/tree）
  - 期望成本：約 `O(1 + α)`
- **Open Addressing（開放定址）**：
  - 元素直接放陣列槽位，碰撞就 probe
  - `α → 1` 時探測長度會明顯增加（效能急降）
  - 工程上常限制 `α` 不要太高（例如 < 0.7）

### 最壞情況為什麼會到 O(n)
- 碰撞嚴重：
  - chaining：全部落同一桶 → 桶長變 `n`
  - open addressing：probe 很長 → 接近掃整張表
- 進階：hash 可被預測時可能被惡意構造 keys 造成退化（HashDoS），因此有些語言會對 hash 做隨機化/抗碰撞設計。

### 好的 Hash Function（對 hash table 而言）
- **Deterministic**：同 key 在同一張表中結果一致
- **Uniform**：輸出分佈接近均勻（避免熱桶）
- **低相關/擾動好**：key 小變動能讓 index 大變動
- **Fast**：hash 計算不該成為瓶頸

# 2. 從 Array + Linked List 演變到 Hash Table

### 從 Array 的限制開始
- Array 只有在 **已知 index** 時才是 O(1)
- 若把 `(key, value)` 塞進 array，`get(key)` 只能 **線性掃描比對 key** → O(n)

### 引入 Buckets（array of lists）
- 建立 `buckets[0..m-1]`，每個 bucket 放一個小容器（常見 linked list）
- 目的：把「全表搜尋」變成「小範圍搜尋」
- 但仍缺：**key 要去哪個 bucket？**（需要規則）

### 引入 Hash Function（決定 bucket）
- 規則：`index = h(key) mod m`
- 操作流程：
  1) 算 index
  2) 直接到 `buckets[index]`
  3) 只在該 bucket 內搜尋/插入/刪除
- Hash Table = **Array（快速定位） + Hash rule（決定位置） + Bucket（處理碰撞）**

### 為什麼會快：O(1 + α)
- Load factor：`α = n / m`
  - n = 元素數、m = bucket 數
  - α = 平均每桶元素數（平均桶長）
- Separate chaining 的期望成本：`O(1 + α)`
- 只要 α 維持常數 → expected O(1)

### Resize / Rehash 的目的
- 當 α 超過門檻 → 擴大 m（常見 ×2）→ **全部重新分配**（rehash）
- 單次 rehash 是 O(n)，但用幾何成長可得到 amortized O(1) 插入

### 常見誤區
- hash 不保證唯一位置 → **碰撞必然存在**
- 效能關鍵取決於：
  - hash 分佈是否均勻
  - α 是否被控制
  - 碰撞策略（chaining / open addressing）

# 3. Collision Resolution

### 為什麼一定會碰撞（Collision）
- key 的可能性遠大於 table 槽位數 `m`，不同 key 可能映射到同一個 index（collision 是必然）。
- 重點不是避免碰撞，而是：**碰撞時仍能讓搜尋範圍很小**。


## 兩大策略：Separate Chaining vs Open Addressing

### 1) Separate Chaining（拉鍊法）
- 做法：每個 index（bucket）存一個小容器（常見 linked list / array / tree）。
- 流程：`index = h(key) mod m` → 只在 `bucket[index]` 內找/插/刪。
- 期望成本：`O(1 + α)`，其中 `α = n/m`（平均 bucket 長度）。
- 優點：
  - 刪除簡單（直接從 bucket 移除）
  - α 變大只是 bucket 變長（退化較溫和）
- 缺點：
  - pointer / allocation overhead
  - cache locality 較差（linked list 跳躍）


### 2) Open Addressing（開放定址）
- 做法：所有 entry 直接放在同一個 array；碰撞就沿 probe sequence 找下一個槽位。
- 優點：
  - cache-friendly（連續陣列）
  - 額外記憶體少（無指標/節點配置）
- 缺點（關鍵）：對 load factor 非常敏感
  - `α → 1` 時 probe 會急遽變長（延遲暴增）
  - 常見工程門檻：`α < 0.7`（避免太滿）

## Open Addressing 的 probe 方式（差異在 clustering）
### Linear Probing（線性探測）
- 規則：`i, i+1, i+2, ...`
- 問題：**Primary clustering**
  - 連續 occupied 區段形成後會越來越長，probe 變慢。

### Quadratic Probing（二次探測）
- 規則：`i + 1^2, i + 2^2, ... (mod m)`
- 改善：降低 primary clustering
- 問題：**Secondary clustering**
  - 同起始 index 的 key 走同一條探測路徑。

### Double Hashing（雙重雜湊）
- 規則：步長由第二個 hash 決定：`i + k*h2(key)`
- 通常分佈最好，可緩解 primary + secondary clustering
- 注意：
  - `h2(key)` 不能為 0
  - 步長需能走遍表（常見要求與 `m` 互質），避免只繞到部分槽位。


## Deletion：為什麼需要 Tombstone（墓碑）
- Open addressing 不能「直接清空」槽位：
  - 會破壞 probe chain，導致後面的 key 查不到（提早在 empty 停止）。
- Tombstone：標記 deleted
  - 查找時不能當停止點（要繼續 probe）
  - 插入時可視策略重用
- 副作用：墓碑累積會拖慢 probe → 需要定期 rehash 清理。


## Clustering（效能崩壞的核心機制）
- Primary clustering：線性探測形成「連續車陣」→ 越撞越長 → probe 越慢。
- Secondary clustering：二次探測同起點 keys 共享探測路徑 → 仍會集中。
- Double hashing：用 key-dependent step size 讓路徑分散，通常最穩。


## Table size（m）的常見取法（在交換風險）
- Prime `m`：較能抵抗某些 hash 偏差（分佈風險較低）
- Power-of-two `m`：可用 bitmask（更快）
  - 但要求 hash 的低位品質要好（需 bit mixing），否則容易偏槽。

# 4. Complexity

## 記號
- `n`：元素數量
- `m`：bucket/slot 數量（table 容量）
- `α = n / m`：load factor（平均擁擠程度）

## 時間複雜度（Expected vs Worst-case）
### Insert / Lookup / Delete
- **Expected**：在 hash 分佈均勻、且 `α` 被控制住時 → 期望 `O(1)`
  - Chaining 更精準：`O(1 + α)`（桶內平均長度是 α）
  - Open addressing：在安全 α 下 probe 次數可維持常數
- **Worst-case**：可能退化成 `O(n)`
  - 例：大量 key 撞在同桶、或 probe chain 超長

### Traversal（遍歷）
- 走訪所有元素：`O(n)`
- 通常 **不保證順序**

### Resize / Rehash
- 單次 rehash：需要重分配 `n` 個元素 → `O(n)`
- 但整體插入可做到 **amortized `O(1)`**

## Amortized O(1)（攤提直覺）
- 常見做法：容量幾何成長（例如 `m *= 2`）
- 多次擴容的搬運總量：`1 + 2 + 4 + ... + n < 2n`
  - 做了 n 次插入，總搬運仍是 `O(n)` → 平均每次插入 `O(1)`
- 實務提醒：rehash 會造成 **latency spike**（單次尖峰），即使攤提很便宜

## 空間複雜度（Big-O + 實務重點）
### Separate Chaining
- 空間：`O(m + n)`
  - m = bucket array，n = entries（含節點/指標等）
- 實務：linked list 有 pointer / allocation overhead，cache locality 較差

### Open Addressing
- 空間：`O(m)`；若 `α` 有界則 `m = Θ(n)` → 整體 `O(n)`
- 實務：必須保留空槽維持低 α（例如 α=0.7 代表槽位約需 1.43n）
# 5. Abstract Data Type

雜湊表 ADT 通常支援以下操作：

### 操作與時間複雜度

- **插入 / Put（Insert / Put）**：新增一組 `(key, value)`。若 key 已存在，則更新其 value。  
  - 期望時間複雜度：`O(1)`  
  - 最壞情況：`O(n)`

- **查找 / Get（Lookup / Get）**：取得 key 對應的 value（或回報不存在）。  
  - 期望時間複雜度：`O(1)`  
  - 最壞情況：`O(n)`

- **更新（Update）**：修改已存在 key 的 value。  
  - 期望時間複雜度：`O(1)`  
  - 最壞情況：`O(n)`

- **刪除 / Remove（Delete / Remove）**：若 key 存在，移除該筆資料。  
  - 期望時間複雜度：`O(1)`  
  - 最壞情況：`O(n)`

- **包含判斷（Contains）**：測試某個 key 是否存在。  
  - 期望時間複雜度：`O(1)`  
  - 最壞情況：`O(n)`

- **遍歷 / 迭代（Traversal / Iteration）**：走訪所有 `(key, value)`（順序通常不保證）。  
  - 時間複雜度：`O(n)`

- **擴容 / 重雜湊（Resize / Rehash）**：在維持載入因子（load factor）於合理範圍時，重建表格並調整容量。  
  - 時間複雜度：`O(n)`

# 6. Pros & Cons

## Pros（優點）
- **期望很快**：在 hash 分佈均勻、load factor 控制良好時，查/插/刪多為 expected `O(1)`。
- **Key 很彈性**：string / number / struct 只要能 hash 就能當 key。
  - 但要注意：`a == b` 必須 ⇒ `hash(a) == hash(b)`（hash 與 equality 要一致）。
- **適合的典型用途**
  - Membership test：`contains(x)`（去重、visited、白名單/黑名單）
  - Dictionary / indexing：`get(key)`（索引、cache、符號表）
  - Counting / aggregation：`count[x]++`（字頻、統計、log 聚合）


## Cons（缺點 / 風險）
- **Worst-case 可能退化到 `O(n)`**
  - 碰撞大量集中（hash 不佳、key 分佈偏、甚至惡意 keys）
  - 常見問題不是平均變慢，而是 **tail latency（P95/P99）變差**。
- **Resize / Rehash 造成延遲尖峰**
  - 單次 rehash 需要搬動所有元素 → 當下 `O(n)`（即使 amortized 仍好看）
  - 緩解方向：預估容量先 reserve、或用漸進式 rehash（視實作而定）
- **通常不保證順序**
  - 遍歷不等於排序；不適合 range query / min-max 這類需求
  - 若要順序：用 balanced BST / skip list / B-tree，或 LinkedHashMap 類型結構
- **Open Addressing 刪除更複雜**
  - 需要 tombstone（墓碑）避免斷 probe chain
  - 墓碑累積會拖慢 probe → 需定期 rehash 清理
  - probing 也可能有 clustering（線性/二次探測的集中問題）
- **需要調參與假設**
  - hash function 品質、load factor 門檻、碰撞策略（chaining vs open addressing）
  - 若無法控制輸入分佈（對外服務）要特別小心碰撞攻擊/偏差


## 什麼時候該用 / 不該用
### 適合
- 主要操作是 `get/put/contains/remove`
- 不需要排序或範圍查詢
- 能接受偶爾的 rehash（或可預估容量）

### 不適合（或要謹慎）
- 需要有序遍歷 / range query / predecessor/successor
- 對 tail latency 極敏感且輸入分佈不可控
- 大量刪除 + open addressing（墓碑管理成本高）

# 7. Variations of Hash



### 1) Robin Hood Hashing（開放定址變體）
- 插入時「probe 距離遠者優先」（把比較近家的元素往後擠）。
- 目標：降低 probe 長度的變異 → **尾延遲更穩**（更可預測）。
- 常搭配 backward-shift deletion 減少 tombstone 依賴。

### 2) Cuckoo Hashing（布穀鳥）
- 多個 hash function；每個 key 有少數候選位置（常見 2 個）。
- Lookup：檢查固定少數槽位 → **worst-case 常數次檢查**（很穩）。
- Insert：可能連鎖踢出（eviction），遇 cycle 需 rebuild/rehash（常設 kick limit / stash）。

### 3) Hopscotch Hashing（跳房子）
- 維持不變量：每個 key 需落在 home bucket 的「鄰域窗口」內（neighborhood）。
- 透過局部搬移把空槽「拉近」，讓 key 留在 home 附近。
- 好處：查找只看小鄰域、cache-friendly；高負載下也常更穩（但實作複雜）。

### 4) Dynamic / Resizing Hash Table（動態擴縮）
- `α` 超門檻就 grow（常 ×2）→ rehash `O(n)`，但插入可 amortized `O(1)`。
- 設計重點是策略：
  - grow/shrink 門檻（含 hysteresis 避免抖動）
  - 一次性 rehash vs 漸進式 rehash（減少 latency spike）

### 5) Perfect Hashing（完美雜湊，靜態集合）
- 針對「固定 key set」建構無碰撞映射 → lookup worst-case `O(1)` 很穩。
- 限制：集合一變動，建表可能要重來。
- 常用在：只讀字典、compiler keywords、常數表。

### 6) Extendible / Linear Hashing（外部記憶體友善）
- 目的：在磁碟/DB 情境避免「全表 rehash」的巨量 I/O。
- 特色：**增量分裂桶**（局部成長），逐步擴容。
  - Extendible：directory 指向 buckets，滿了就 split 並局部更新
  - Linear：按順序逐桶 split，漸進擴展

  