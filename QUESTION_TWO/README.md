# Question Two: Hospital Laboratory Sample Queue System

This folder models a hospital laboratory sample queue using a doubly linked list in C.

## Files Included
- `questiontwo.c`: The C source code implementing the doubly linked list, tail pointer optimization, menu navigation, and safe memory management.

---

## Algorithm Analysis

1. **Time Complexity of Adding a New Sample:**
   - **With a Tail Pointer ($O(1)$):** Our implementation maintains a direct reference pointer (`tail`) to the last node. Adding a new sample happens in constant time ($O(1)$) without traversing the list.
   - **Without a Tail Pointer ($O(n)$):** Would require traversing all $n$ nodes from the head to reach the end.

2. **Time Complexity of Traversing Samples:**
   - Traversing all $n$ samples in either direction via `next` or `prev` pointers takes linear time, $O(n)$.
