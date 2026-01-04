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
