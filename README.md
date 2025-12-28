# Browser History Data Structure

A robust C implementation of a Browser History system, simulating the logic found in web browsers (and LeetCode problem 1472). This project uses a **Doubly Linked List** (or dynamic stack) approach to manage visited URLs, allowing for efficient `O(1)` backwards and forward navigation.

## Project Structure

| File | Description |
| :--- | :--- |
| `browser_history.h` | Header file defining the `BrowserHistory` struct and function prototypes. |
| `browser_history.c` | Core logic implementation (Visit, Back, Forward, Free). |
| `test_main.c` | Test runner that parses `.txt` files to automate testing. |
| `tests.txt` | Basic test cases for standard functionality. |
| `deep_test.txt` | Advanced test cases for deep navigation and history overwrites. |
| `CMakeLists.txt` | Configuration file for building the project with CMake. |

## Features

- **Initialize**: Start a new browser session with a homepage.
- **Visit**: Navigate to a new URL (clears forward history).
- **Back**: Move back `steps` in history.
- **Forward**: Move forward `steps` in history.
- **Memory Management**: specific functions to free allocated memory preventing memory leaks.

## Build & Run

### Option 1: Using GCC (Quickest)
You can compile the source files directly in your terminal:

```bash
# Compile the project
gcc test_main.c browser_history.c -o browser_app

# Run with a specific test file
./browser_app tests.txt
