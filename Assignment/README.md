# CS203A – Data Structures  
## Homework Repository

**Student Name:** 黃翊逢  
**Student ID:** 1123301  
**Course:** CS203A – Data Structures  

This repository contains my homework assignments for the **CS203A Data Structures** course.  
It serves as a **living record of my learning progress**, covering both theoretical concepts and practical analysis of fundamental data structures.

---

## Course Overview

The CS203A course introduces core data structures and emphasizes:

- Structural properties of data organizations  
- Algorithm behavior on different data structures  
- Time and space complexity analysis  
- Appropriate real-world applications of each structure  

Across the assignments, I explored arrays, linked lists, hashing, and trees, gradually building a deeper understanding of how data structures affect performance and design decisions.

---

## Assignment Overview

- **Assignment I – Build Your Own GitHub Repository**
- **Assignment II – Array Selection Sort**
- **Assignment III – Linked List Selection Sort**
- **Assignment IV – Hash Function Design**
- **Assignment V – Tree Data Structures**

---

## Assignment Summaries

### 🔹 Assignment I: Build Your Own GitHub Repository
**Core focus:**
- Creating a professional GitHub account
- Setting up a public course repository
- Writing documentation using Markdown
- Publishing a personal homepage with GitHub Pages

**Key learning outcomes:**
- Understanding basic GitHub workflow (repository, commit, public/private)
- Learning how to write structured README.md files
- Using GitHub Pages as a static website for course presentation
- Treating a repository as a long-term learning archive rather than a one-time submission

---

### 🔹 Assignment II: Array Selection Sort
**Core focus:**
- Array structure and index-based access
- Manual execution of selection sort
- Tracing swaps and minimum selection step by step

**Key learning outcomes:**
- Understanding how selection sort works internally
- Observing O(n²) time complexity through repeated traversal
- Recognizing the advantages of arrays, such as O(1) random access

---

### 🔹 Assignment III: Linked List Selection Sort (Swap Value Version)
**Core focus:**
- Singly linked list representation
- Pointer-based traversal
- Applying selection sort logic to linked lists

**Key learning outcomes:**
- Comparing arrays and linked lists in terms of access and traversal cost
- Understanding why linked lists require O(n) access time
- Learning how swapping values (instead of nodes) simplifies linked list sorting

---

### 🔹 Assignment IV: Hash Function Design & Analysis
**Core focus:**
- Designing hash functions for integers and strings
- Comparing multiplicative hashing and squared hashing
- Evaluating collision behavior under different table sizes

**Key learning outcomes:**
- Understanding the importance of prime table sizes
- Observing clustering and collision patterns
- Learning how hash function design directly impacts performance

**Implementation highlights:**
- Implemented in both C and C++
- Tested with multiple datasets and table sizes
- Analyzed results through distribution and collision comparison

---

### 🔹 Assignment V: Tree Data Structures
**Core focus:**
- Understanding the tree family hierarchy
- Constructing multiple tree variants using the same dataset
- Comparing balancing strategies and applications

**Tree structures studied:**
- General Tree  
- Binary Tree  
- Complete Binary Tree  
- Binary Search Tree (BST)  
- AVL Tree  
- Red-Black Tree  
- Max Heap  
- Min Heap  

**Key learning outcomes:**
- Understanding how additional constraints specialize trees
- Comparing strict balance (AVL) vs. relaxed balance (Red-Black)
- Learning why heaps are ideal for priority-based problems

---

## Overall Reflection

Through these assignments, I developed a clearer understanding of how **data structure design influences algorithm efficiency and system behavior**.

Starting from **Assignment I**, I learned the importance of organizing work properly using GitHub and Markdown. This foundation made later assignments easier to manage and present clearly.

In **Assignments II and III**, comparing arrays and linked lists highlighted how the same algorithm behaves very differently depending on the underlying data structure. Arrays provide fast access but fixed structure, while linked lists offer flexibility at the cost of traversal efficiency.

**Assignment IV** demonstrated that performance is not only about algorithms, but also about design choices such as hash functions and table sizes. Even small design differences can significantly affect collision behavior and efficiency.

Finally, **Assignment V** helped me understand the broader family of tree data structures. Seeing how Binary Trees evolve into BSTs, AVL Trees, Red-Black Trees, and Heaps clarified the relationships between structure, constraints, and applications. I also learned that no single data structure is universally optimal—each involves trade-offs depending on the use case.

Overall, this course strengthened my ability to:
- Analyze data structures beyond definitions
- Connect theoretical properties to real-world use cases
- Make informed decisions when choosing appropriate data structures

---

## Repository Structure

```text
CS203A/
│── README.md              # Course overview and reflection
│── AssignmentI/
├── AssignmentII/          # Array Selection Sort
├── AssignmentIII/         # Linked List Selection Sort
├── AssignmentIV/          # Hash Function Design (C / C++)
└── AssignmentV/           # Tree Structures
