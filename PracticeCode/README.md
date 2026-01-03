# C 語言資料結構學習範例  
## Array 與 Linked List 的動態記憶體配置

此資料夾包含數個 **用於學習與觀察 C 語言資料結構與動態記憶體配置方式** 的範例程式。  
這些程式的主要目的是幫助我理解：

- 一維與二維 Array 在動態記憶體（`malloc`）下的配置方式
- 指標（pointer）與記憶體位址之間的關係
- Linked List 節點如何透過 `malloc` 建立並使用指標串接
- 動態記憶體配置與釋放的正確使用方式

---

## 檔案說明

### `array_dynamic_memory.c`
**主題：一維 / 二維陣列的動態記憶體配置**

- 示範如何使用 `malloc` 配置一維動態陣列（`int *`）
- 透過實際操作與位址觀察，理解陣列在記憶體中是連續配置的
- 包含二維動態陣列（`int **`）的配置方式，用來說明：
  - row 指標的配置
  - 每一列 column 記憶體的獨立配置
- 幫助理解二維陣列在記憶體中的實際結構

---

### `array_demo_incomplete.c`
**主題：Array 動態記憶體與指標操作示範**

- 示範一維與二維 Array 在動態記憶體下的使用方式
- 著重於：
  - 指標與陣列之間的關係
  - 陣列元素存取方式
  - 記憶體位址的配置與操作

---

### `linked_list_memory.c`
**主題：Linked List 的動態記憶體配置與指標串接**

- 示範如何定義 linked list 節點（node 結構）
- 使用 `malloc` 動態建立節點
- 透過 `next` 指標將多個節點串成一條 linked list
- 包含：
  - 節點建立
  - linked list 的 traversal（走訪）
  - linked list 記憶體釋放
- 幫助理解 linked list 與 array 在記憶體配置上的本質差異

