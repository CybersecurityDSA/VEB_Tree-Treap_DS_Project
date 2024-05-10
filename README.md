# VEB_Tree-Treap_Data_Structures_Project 

*Team 2 Members:*
1) Dharaneesh Panneer Selvam
2) Gangesh Rameshkumar
3) Sanjit Muralikrishnan
4) Abhishek Prattipati
5) Shashaank Subramannya
6) Jyotiraditya Cheemakuruthi
7) Tania Panjagala
8) Manya Khandelwal
9) Ansh Mishra
10) Garry Perumal Roy

## VEB-Trees

This project implements a VEB-Tree (van Emde Boas Tree), a data structure for storing and manipulating integer keys within a defined universe.

### Key Features:

- __Efficient operations:__
  - Search, Insert, and Delete: O(log log N) time complexity (N being the universe size)
  - Minimum and Maximum retrieval: O(1) time complexity
- __Applications:__
  - Priority queues
  - Specialized dictionaries requiring efficient handling of large sets of integers.

### Advantages

- __Remarkably Fast Operations:__ VEB trees boast exceptional time complexity for search, successor, predecessor, insert, and delete operations. These operations are achieved in O(log log n) time, which is significantly faster than standard balanced search trees like AVL trees or red-black trees (O(log n)). This makes VEB trees ideal for applications where speed is critical and dealing with a large universe of integers.
- __Efficient for Limited Range:__ VEB trees shine when dealing with a set of integers within a known, limited range. Unlike other search trees that can handle any integer value, VEB trees are optimized for a specific range (e.g., integers from 0 to 2^k). This focus allows them to achieve their superior time complexity within that defined range.
- __Dynamic Set Maintenance:__ VEB trees are well-suited for maintaining dynamic sets of integers. They efficiently handle insertions and deletions while keeping the search structure balanced, making them a good choice for applications where the data set is constantly changing.

### Further Considerations:

- While offering superior time complexity (O(log log N)) compared to basic data structures, VEB-Trees have a higher constant factor in their runtime. This trade-off is ideal for scenarios involving frequent operations on a vast universe of keys.

## Treaps

Treaps are a type of self-balancing binary search tree that offer efficient search, insertion, and deletion operations with an interesting twist: they achieve balance probabilistically. This document provides a brief overview of treaps, highlighting their advantages and considerations for use.

### Key Features:

- Treaps excel at operations like search, insert, and delete, offering logarithmic time complexity (O(log n)) in expectation. This makes them efficient for dynamic data sets.
- Treaps support unique "split" and "join" operations that allow efficient manipulation of subtrees based on key values. This can be useful for specific algorithms dealing with ranges or partitions of data.

### Advantages:

- __Simple Implementation:__ Compared to other self-balancing trees like AVL trees or red-black trees, treaps offer a simpler implementation.
- __Efficient Operations:__ Similar to other balanced search trees, treaps guarantee logarithmic time complexity (O(log n)) for search, insert, and delete operations in expectation.
- __Split and Join Operations:__ Treaps support efficient split and join operations, which can be useful for certain algorithms.
  
### Further Considerations:

- __Probabilistic Guarantees:__ Unlike AVL trees or red-black trees, which guarantee balance in all cases, treaps rely on random priorities assigned to nodes. This means the worst-case performance can be skewed, although the probability of such cases is low.
- __Limited Practical Use:__ While interesting theoretically, treaps haven't gained widespread adoption in standard libraries due to the reliance on random priorities and the existence of well-established balanced search tree implementations.
