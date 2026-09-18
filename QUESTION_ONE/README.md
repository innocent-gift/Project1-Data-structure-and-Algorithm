# Question One: E-Commerce Order Priority Sorting

This folder contains the implementation for processing and prioritizing daily e-commerce orders using a custom Quick Sort algorithm in C.

## Files Included
- `questionone.c`: The C source code implementing dynamic memory allocation, file reading/writing, and custom Quick Sort based on warehouse priorities.
- `orders.txt`: Input text file containing raw order data.
- `priority_orders.txt`: Generated output file containing sorted orders according to priority rules.

---

## Algorithm Analysis

For the custom Quick Sort implementation, the complexities are as follows:

* **Best Case ($O(n \log n)$):** Occurs when the partitioning step always divides the array into two nearly equal halves. The recurrence relation is $T(n) = 2T(n/2) + O(n)$.
* **Average Case ($O(n \log n)$):** Over all possible random arrangements of input orders, the pivot divides the array into relatively balanced proportions on average.
* **Worst Case ($O(n^2)$):** Occurs when the chosen pivot consistently results in highly unbalanced partitions (e.g., picking the smallest or largest element every time on already sorted data). The recurrence becomes $T(n) = T(n - 1) + O(n)$.
* **Auxiliary Space Complexity ($O(\log n)$):** Quick Sort operates **in-place** on the array, requiring extra memory only for the recursion call stack, which has a maximum depth of $\log n$ in the best and average cases.

---

## Critical Evaluation: Quick Sort vs. Insertion Sort

As the e-commerce company grows, Quick Sort is significantly more appropriate than Insertion Sort for the following reasons:

1. **Dataset Size:** Insertion Sort works well for tiny datasets ($n < 30$), but as daily orders scale into thousands or millions, its performance drops drastically. Quick Sort is engineered specifically for large-scale data handling.
2. **Expected Running Time:** Insertion Sort runs in $O(n^2)$ time on average and in the worst case, whereas Quick Sort runs in $O(n \log n)$ on average. For large order volumes, $n \log n$ executes operations exponentially faster.
3. **Scalability:** Quick Sort scales gracefully. Doubling the order volume causes a predictable, manageable increase in processing time, whereas Insertion Sort quadruples the processing time when data is doubled.
4. **Behavior:** While Insertion Sort has a fast best-case ($O(n)$ for already sorted data), its average/worst-case behavior is slow and causes bottlenecks. Quick Sort maintains strong average performance and high cache locality.
5. **File Storage Context:** Orders are initially read from a flat file into continuous RAM. Quick Sort excels with contiguous memory arrays through in-place partitioning, whereas Insertion Sort would repeatedly shift massive blocks of memory, adding severe performance overhead.
