# Question Four: Hospital Pharmacy Inventory System

This folder contains a C program that loads hospital pharmacy records from a text file into a Binary Search Tree (BST) indexed by medicine codes for fast lookup, along with duplicate handling, in-order traversal, and robust memory management.

## Files Included
- `questionfour.c`: C source code implementing file parsing, data validation, BST insertion with duplicate updates, code-based search, in-order display, and memory deallocation.
- `inventory.txt`: Text file containing medicine records in pipe-separated format.

---

## Algorithm Analysis

For a BST containing $n$ nodes:

* **Time Complexity of Searching:** $O(h)$, where $h$ is the height of the tree.
* **Best Case ($O(\log n)$):** Occurs when the BST is perfectly balanced. Each comparison cuts the remaining search space in half.
* **Average Case ($O(\log n)$):** For randomly inserted data, the tree stays relatively balanced, yielding logarithmic search times.
* **Worst Case ($O(n)$):** Occurs when records are inserted in strictly sorted order, turning the BST into a skewed linear tree (similar to a linked list).

---

## Conceptual Understanding

### 1. Binary Tree vs. Binary Search Tree (BST)
* **Binary Tree:** A hierarchical tree data structure where every node has at most two children (left and right), with no specific ordering rules applied to the node values.
* **Binary Search Tree (BST):** A specialized binary tree that satisfies the ordering property: for any node, all values in its left subtree are smaller than its key, and all values in its right subtree are greater than its key.

### 2. Linear File Search vs. In-Memory BST Search
* **Linear Search on Text File:** Requires scanning through the file line-by-line from disk storage every time a search is performed, leading to an $O(n)$ time complexity with high I/O disk latency.
* **BST Search in Memory:** Loads records into RAM once during startup. Subsequent searches traverse pointers in memory without hitting the disk, achieving efficient $O(\log n)$ performance.

### 3. Construction Cost vs. Multiple Searches Benefit
* **Construction Cost:** Building the BST takes $O(n \log n)$ time initially because it parses the file and inserts nodes into memory.
* **Operational Benefit:** While building has an upfront cost, it is performed only once. When the pharmacy staff performs dozens or hundreds of daily lookups, the fast $O(\log n)$ lookup time drastically outperforms repeated linear file scanning, making the BST approach much more efficient for growing businesses.
