# Browser History Data Structure

A robust C implementation of a Browser History system, simulating the logic found in modern web browsers (and LeetCode problem 1472).

##  Overview

This project implements the browser history using a **Dynamic Array (Tableau)** approach. Unlike a Linked List, this implementation utilizes a contiguous block of memory and integer indices to track the current position. 

**Key Advantages:**
* **O(1) Time Complexity:** Instant access for `Back` and `Forward` operations (no pointer traversal required).
* **Amortized O(1) Visit:** Uses geometric resizing (doubling capacity) when the history array is full.
* **Cache Locality:** Contiguous memory allocation improves CPU cache performance compared to scattered linked list nodes.

##  Project Structure

| File | Description |
| :--- | :--- |
| **browser_history.h** | Header file defining the `BrowserHistory` struct and function prototypes. |
| **browser_history.c** | Core logic implementation (Dynamic Array logic: `malloc`, `realloc`, index math). |
| **test_main.c** | Test runner that parses `deep_test.txt` to automate testing. |
| **deep_test.txt** | specific test cases for deep navigation, history overwrites, and boundary checks. |
| **CMakeLists.txt** | (Optional) Configuration file if building with CMake. |

##  Features

* **Initialize:** Start a new browser session with a homepage.
* **Visit:** Navigate to a new URL.
    * *Logic:* Clears all forward history. If the internal array is full, it automatically resizes.
* **Back:** Move back `steps` in history using direct index subtraction.
* **Forward:** Move forward `steps` in history using direct index addition.
* **Memory Management:** Includes cleanup functions to free all allocated strings and the array structure to prevent memory leaks.

##  Build & Run

### 1. Compilation
You can compile the source files directly using GCC:

```bash
gcc test_main.c browser_history.c -o browser_app -Wall -Wextra
