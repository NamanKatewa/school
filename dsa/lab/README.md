Generate modern, idiomatic C++17 code (no `bits/stdc++.h`, use `<vector>`, `<iostream>`, `<string>`, `<chrono>`, `<memory>`, `<stdexcept>`, etc.).  
Follow this spec exactly: class names, method names, behavior, and separation by modules/labs.

Implement everything as separate `.hpp`/`.cpp` pairs where it makes sense, but you may inline simple functions in class definitions if you prefer.  
Prefer references (`const T&`) over copies where appropriate, and avoid raw `new`/`delete` outside of internal data-structure code.

---

## Lab 1 – Array operations module

Create a generic fixed-capacity array wrapper for `int` (no templates needed for now), with logical size tracking and all these operations.

### Class: `Array`

**Data members**

- `int *data;` // pointer to dynamic array buffer
- `int capacity;` // maximum number of elements
- `int size;` // current logical size

**Constructors / destructor**

- `Array(int capacity);` // allocate buffer, initialize `size = 0`
- `~Array();` // free buffer

**Basic operations**

- `int getSize() const;`
- `int getCapacity() const;`
- `bool isEmpty() const;`
- `bool isFull() const;`

- `void input(int n);`

  - Read `n` integers from `std::cin` and fill array from index 0.
  - Set `size = n` (assume `n <= capacity`).

- `void display() const;`
  - Print all elements with indices in order.

**Access / update**

- `int getAt(int index) const;`

  - Return element at `index`.
  - Throw `std::out_of_range` if `index` is invalid.

- `void setAt(int index, int value);`
  - Set element at `index` to `value`.
  - Throw `std::out_of_range` if `index` is invalid.

**Insertion / appending**

- `void append(int value);`

  - Insert at end if not full, increment `size`.
  - Throw if full.

- `void insertAt(int index, int value);`

  - Insert `value` at `index` (0-based).
  - Shift elements from `index..size-1` one step to the right.
  - Throw if full or index is not in `[0, size]`.

- Convenience wrappers:
  - `void insertFront(int value);` // alias of `insertAt(0, value)`
  - `void insertBack(int value);` // alias of `append(value)`

**Search – first and all occurrences**

- `int searchFirst(int key) const;`

  - Linear search from left to right.
  - Return index of first occurrence or `-1` if not found.

- `std::vector<int> searchAll(int key) const;`

  - Return a vector of all indices where `data[i] == key`.

- `int countOccurrences(int key) const;`
  - Return the number of elements equal to `key`.

**Deletion – by index, first occurrence, all occurrences**

- `void deleteAt(int index);`

  - Remove element at `index`.
  - Shift elements left from `index+1..size-1`.
  - Decrement `size`.
  - Throw if index invalid.

- `bool deleteFirstByValue(int key);`

  - Find first occurrence with `searchFirst`.
  - If found, call `deleteAt(index)` and return `true`.
  - If not found, return `false`.

- `int deleteAllByValue(int key);`
  - Remove **all** elements equal to `key` using in-place compaction:
    - Keep write index `j = 0`.
    - For each `i` in `[0, size)`, if `data[i] != key`, write `data[j++] = data[i]`.
  - Update `size = j`.
  - Return number of elements removed.

**Aggregate and utility operations**

- `int minElement() const;` // assume non-empty; throw if empty
- `int maxElement() const;`
- `long long sum() const;`
- `double average() const;` // for non-empty; throw if empty

- `void reverse();`

  - Reverse array in place.

- `void rotateLeft(int k);`
- `void rotateRight(int k);`
  - Implement rotation using modular arithmetic; handle `k >= size`.

---

## Lab 2 – General Time and Space Complexity Measurement

Design a reusable module that can empirically measure and report the time and space complexity of arbitrary functions over varying input sizes.

Create a generic module that can run any user‑supplied algorithm (function, lambda, functor) on a range of input sizes and then print timing and operation/memory usage statistics in tabular form.

### Class: `ComplexityDemo`

**Data members**

- No mandatory instance data members.
- Utility helpers may be declared `static` or as free functions within the implementation file.

**Public interface**

- `static void runAllDemos();`
  - Drives multiple experiments over increasing input sizes.
  - For each selected test function and input size, records:
    - Input size parameter (for example, \(n\)
    - Execution time
    - Operation and/or memory usage metrics (if provided by the function)
  - Prints results as tables, one table per measured function.

### Supported function types and measurement

The framework should not be limited to specific algorithms like max, search, or sorting. Instead, it should support any callable that fits one of the following patterns:

- Pure time measurement (no explicit operation count):

  - `ReturnType func(InputType &input);`

- Time + operation count:

  - `ReturnType func(InputType &input, long long &operationCount);`

- Time + operation count + custom metrics (optional):

  - `ReturnType func(InputType &input, long long &operationCount, CustomMetrics &metrics);`

The module should allow registering such functions together with:

- A name/label used in the output.
- A generator function that, given \(n\), constructs appropriate input data of size \(n\).

### Example function wrappers

These are _examples only_ to illustrate how a client might plug in specific algorithms. The framework itself must remain generic:

- Constant‑time example (e.g., array access):

  - `static int constantTimeExample(const Array &arr);`

- Linear‑time example (e.g., find max):

  - `static int linearMax(const Array &arr, long long &comparisonCount);`

- Quadratic‑time example (e.g., nested loops):

  - `static int quadraticDummy(int n, long long &operationCount);`

- Optional (for demonstrating \(O(\log n)\) and \(O(n \log n)\)):

  - `static int binarySearch(const std::vector<int> &arr, int key, long long &comparisonCount);`
  - `static void mergeSort(std::vector<int> &arr, long long &comparisonCount);`

These are _clients_ of the general measurement utilities, not hard‑coded into the design.

### Timing utility

Provide a reusable timing helper that can wrap any callable:

- `template <typename Func> static long long measureTimeMillis(Func f);`
  - Uses `std::chrono::high_resolution_clock` (or `steady_clock`) to measure the elapsed time.
  - Returns elapsed time in milliseconds as a `long long`.
  - Intended to be used with lambdas capturing the function and its arguments.

### Optional space/memory measurement

If desired, extend the framework to capture approximate space complexity by:

- Counting allocated elements within the input (for containers).
- Or integrating with a custom allocator or platform‑specific memory measurement utilities (out of scope for strict portability, but the API can be designed to accept such metrics).

For example, client code could compute:

- `sizeInBytes = input.size() * sizeof(ElementType);`

and pass it back in a metrics structure that the framework then prints.

### Main / driver behavior

The `main` function (or a higher‑level driver) should:

- Define a set of input sizes, for example:

  - \(n \in \{10^3, 10^4, 10^5\}\) (or any configurable sequence).

- For each registered function:

  - For each \(n\) in the chosen sequence:
    - Construct input data of size \(n\) (via a generator).
    - Run the function through the measurement helper.
    - Obtain:
      - \(n\)
      - `time_ms`
      - `operationCount` (if supported by that function)
      - Any additional metrics (if defined).

- Print the results as rows of a table, e.g.:

  - `(n, time_ms, operationCount)`
  - Or extended: `(n, time_ms, operationCount, memoryBytes, ...)`.

This design generalizes the lab from measuring a fixed set of sample algorithms to a reusable tool that can empirically analyze time and (optionally) space complexity for any compatible function.

---

## Lab 3 – Singly linked list with full array-like operations

Implement a singly linked list class that mirrors the `Array` functionality wherever it makes sense.

### Struct / class: `ListNode`

- `int data;`
- `ListNode *next;`

### Class: `SinglyLinkedList`

**Data members**

- `ListNode *head;`
- `int size;` // maintain logical size for convenience

**Constructors / destructor**

- `SinglyLinkedList();` // `head = nullptr`, `size = 0`
- `~SinglyLinkedList();` // delete all nodes

**Basic operations**

- `int getSize() const;`
- `bool isEmpty() const;`

- `void clear();`

  - Delete all nodes and reset `head` and `size`.

- `void display() const;`
  - Print full list from head to tail.

**Access / update by index (array-like)**

- `int getAt(int index) const;`

  - Traverse from head to the node at position `index`.
  - Throw `std::out_of_range` if invalid.

- `void setAt(int index, int value);`
  - Traverse and modify data at position `index`.

**Insertion**

- `void insertFront(int value);`

  - Insert new node at head.

- `void insertBack(int value);`

  - Insert new node at tail (traverse or maintain a tail pointer if you like).

- `void insertAt(int index, int value);`
  - Insert at 0..size, re-link pointers accordingly.
  - Throw if `index` not in `[0, size]`.

**Deletion by index**

- `void deleteFront();`
- `void deleteBack();`
- `void deleteAt(int index);`
  - Handle edge cases (`index == 0`, last element).

**Search – first and all occurrences**

- `int searchFirst(int key) const;`

  - Return index of first node whose data equals `key`, or `-1`.

- `std::vector<int> searchAll(int key) const;`

  - Return vector of indices where nodes match `key`.

- `int countOccurrences(int key) const;`

**Deletion by value – first and all occurrences**

- `bool deleteFirstByValue(int key);`

  - Unlink first node with `data == key`, adjust `head`, and update `size`.

- `int deleteAllByValue(int key);`
  - Traverse the whole list, remove every node with `data == key`.
  - Be careful with consecutive matches at head.
  - Return count of deleted nodes.

**Utility operations**

- `void reverse();`

  - Iteratively reverse list pointers (`prev`, `curr`, `next`).

- `void concatenate(SinglyLinkedList &other);`

  - Append all nodes from `other` to this list, leaving `other` empty.

- Optional: `void sort();`
  - Implement simple linked-list sort, e.g., insertion sort or bubble sort on nodes.

---

## Lab 4 – Stacks and queues (arrays and linked lists)

Implement stack and queue ADTs both with arrays and with linked lists, reusing `ListNode` where appropriate.

### Stack using array – class `StackArray`

**Data members**

- `int *data;`
- `int capacity;`
- `int top;` // index of top element or -1 when empty

**Interface**

- `StackArray(int capacity);`
- `~StackArray();`

- `bool isEmpty() const;`
- `bool isFull() const;`

- `void push(int value);`
- `int pop();`
- `int peek() const;`

- `void display() const;` // from top to bottom

---

### Stack using linked list – class `StackList`

**Data members**

- `ListNode *top;`
- `int size;`

**Interface**

- `StackList();`
- `~StackList();`

- `bool isEmpty() const;`
- `int getSize() const;`

- `void push(int value);` // insert at head
- `int pop();` // remove from head
- `int peek() const;`

- `void display() const;`

---

### Queue using array (circular) – class `QueueArray`

**Data members**

- `int *data;`
- `int capacity;`
- `int front;` // index of front element
- `int rear;` // index of last element
- `int size;`

**Interface**

- `QueueArray(int capacity);`
- `~QueueArray();`

- `bool isEmpty() const;`
- `bool isFull() const;`

- `void enqueue(int value);`
- `int dequeue();`
- `int getFront() const;`
- `int getRear() const;`

- `void display() const;` // from front to rear

---

### Queue using linked list – class `QueueList`

**Data members**

- `ListNode *front;`
- `ListNode *rear;`
- `int size;`

**Interface**

- `QueueList();`
- `~QueueList();`

- `bool isEmpty() const;`
- `int getSize() const;`

- `void enqueue(int value);` // insert at tail
- `int dequeue();` // remove from head
- `int getFront() const;`
- `int getRear() const;`

- `void display() const;`

---

## Lab 5 – Postfix expression evaluation using stack

Use one of your stack implementations (prefer `StackArray`) to evaluate postfix expressions.

### Class: `PostfixEvaluator`

**Data members**

- none, or static-only utilities

**Interface**

- `static int evaluate(const std::string &expr);`
  - `expr` is a postfix expression with tokens separated by spaces (e.g. `"2 3 4 * +"`).
  - Support integer operands and operators: `+ - * / ^`.

**Behavior**

- Tokenize the input string (e.g., `std::istringstream`).
- If token is an integer: push onto operand stack.
- If token is an operator:
  - Pop two operands `b = pop()`, `a = pop()`.
  - Compute `a op b`, push result.
- At end, stack must contain exactly one element, which is the result.
- Throw on errors:
  - Not enough operands.
  - Extra operands remaining.
  - Division by zero.
  - Invalid tokens or operators.

Optional:

- Add support for unary minus if you want (document behavior).

---

## Lab 6 – Linear and binary search

Implement searching algorithms with comparison counting.

### Class: `SearchAlgorithms`

All methods should be `static`.

**Linear search**

- `static int linearSearchFirst(const std::vector<int> &arr, int key, long long &comparisons);`
- `static std::vector<int> linearSearchAll(const std::vector<int> &arr, int key, long long &comparisons);`

**Binary search (on sorted array)**

- `static int binarySearchIterative(const std::vector<int> &arr, int key, long long &comparisons);`
- `static int binarySearchRecursive(const std::vector<int> &arr, int key, long long &comparisons);`

**First/last occurrence variants (sorted array)**

- `static int binarySearchFirst(const std::vector<int> &arr, int key, long long &comparisons);`
- `static int binarySearchLast(const std::vector<int> &arr, int key, long long &comparisons);`

---

## Lab 7 – Sorting algorithms (Insertion, Selection, Bubble)

Implement classic in-place sorts with comparison and swap counters.

### Class: `SortingAlgorithms`

All methods `static`.

**Common pattern**

Each algorithm should have the signature:

- `static void bubbleSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &swaps);`
- `static void selectionSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &swaps);`
- `static void insertionSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &shifts);`

**Behavior**

- `ascending == true` => sort ascending, else descending.
- Count every comparison between elements in `comparisons`.
- For Bubble/Selection, count element swaps in `swaps`.
- For Insertion, count shifts/moves of elements in `shifts`.

Optionally add helper:

- `static void printStats(const std::string &name, int n, long long comparisons, long long moves);`

---

## Lab 8 – Binary tree and traversals

Implement a Binary Search Tree (BST) with core operations and traversals.

### Struct / class: `TreeNode`

- `int data;`
- `TreeNode *left;`
- `TreeNode *right;`

### Class: `BinarySearchTree`

**Data members**

- `TreeNode *root;`

**Constructors / destructor**

- `BinarySearchTree();`
- `~BinarySearchTree();` // delete all nodes (postorder deletion)

**Insertion and search**

- `void insert(int value);`

  - Insert a new value following BST property.

- `bool search(int value) const;`

**Traversals**

All traversals should have two versions: recursive private helper plus public wrapper that prints values.

- `void preorder() const;`
- `void inorder() const;`
- `void postorder() const;`
- `void levelOrder() const;` // use `std::queue<TreeNode*>`

**Utility operations**

- `int height() const;`
- `int countNodes() const;`
- `int countLeaves() const;`
- `int countInternalNodes() const;`

- `int minValue() const;` // smallest element in BST
- `int maxValue() const;`

Optional:

- `void mirror();` // recursively swap left/right children
- `void clear();` // delete all nodes and set `root = nullptr`

---
