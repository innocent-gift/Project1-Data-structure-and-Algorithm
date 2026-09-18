# Question Three: E-Sports Tournament Binary Tree Management

This folder contains a C program implementing a binary tournament tree using Binary Search Tree (BST) insertion rules, complete with a menu-driven interface for relationship queries and robust memory management.

## Files Included
- `questionthree.c`: The C source code implementing dynamic node creation, BST insertion, tree traversal, search queries, and memory deallocation.

---

## Algorithm Analysis & Complexity

### Time Complexity of Inserting a New Node ($n$ nodes)
- **Average Case ($O(\log n)$):** When the binary search tree remains reasonably balanced, insertion requires traversing down the height of the tree, which is proportional to $\log_2(n)$.
- **Worst Case ($O(n)$):** If the input participant identifiers are presented in a strictly sorted (ascending or descending) order, the BST degenerates into a linear linked list (skewed tree). In this worst-case scenario, inserting a new node requires traversing all $n$ nodes to reach the bottom.

### Justification
The insertion strategy uses standard Binary Search Tree rules where elements smaller than the current node move left, and elements greater move right. The search and insertion depth directly depends on the tree's height ($h$), giving a time complexity of $O(h)$, which ranges from $O(\log n)$ for balanced trees to $O(n)$ for completely skewed trees.
