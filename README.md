# `get_next_line` project

---

## **Project Structure**

```
get_next_line_project/
├── get_next_line.h          ──> Header for prototypes, includes, and macros
├── get_next_line.c          ──> Main file handling line retrieval logic
├── get_next_line_utils.c    ──> Utility functions for line processing
├── bonus/                   ──> Bonus-specific files (optional)
│   ├── get_next_line_bonus.c
│   ├── get_next_line_utils_bonus.c
│   └── get_next_line_bonus.h
└── tests/                   ──> Folder for tests
    ├── test_get_next_line.c ──> Main test file for get_next_line
    └── test_bonus.c         ──> Test cases specific to bonus part

```
---

## **Roadmap Phases**

### **Phase 1: Preparation and Planning**

1. **Read and Analyze Requirements**:
    - Focus on mandatory functionality: handling of `BUFFER_SIZE`, reading lines one by one, and handling both file and standard input.
    - Understand limitations: no global variables, no `lseek()`, and no `libft` usage.
2. **Set Up Repository and Structure**:
    - Initialize a Git repository and structure folders as shown.
3. **Makefile Creation**:
    - Include basic rules: `all`, `clean`, `fclean`, `re`, and `bonus`.
    - Add compilation flags (`Wall -Wextra -Werror`) and ensure `BUFFER_SIZE` is configurable.

**Estimated Time**: 5 hours

---

### **Phase 2: Core Functionality - get_next_line**

### 2.1 **Implementing Core Reading Logic**

1. **Develop `get_next_line` in `get_next_line.c`**:
    - Initialize `BUFFER_SIZE` and manage file descriptor reads with `read()`.
    - Use a static buffer for data persistence across multiple calls.
    - Ensure `BUFFER_SIZE` can handle different sizes (e.g., 1, 9999) without memory leaks.
2. **Line Segmentation**:
    - Implement logic to store read data and break when encountering a newline character.
    - Ensure that each returned line ends with `\n` (if the end of the file doesn’t naturally include it).

### 2.2 **Auxiliary Functions in `get_next_line_utils.c`**

- Write helper functions for:
    - **Buffer Management**: Functions to manage and transfer buffer data.
    - **Line Storage**: Functions for dynamic allocation to store or expand line data until newline or EOF.
    - **Memory Safety**: Allocate and free memory dynamically, preventing memory leaks.

**Estimated Time**: 10 hours

---

### **Phase 3: Testing and Debugging Core**

1. **Write Unit Tests**:
    - Test typical cases (normal lines, end with and without newline).
    - Edge cases with varying `BUFFER_SIZE` (1, 42, 9999).
    - Validate memory safety using `valgrind` for memory leaks and ensure tests cover normal files, empty files, and standard input.
2. **Error Handling**:
    - Ensure `NULL` is returned for errors and EOF.
    - Use static variables correctly without introducing undefined behavior or memory issues.

**Estimated Time**: 8 hours

---

### **Phase 4: Implementing Bonus Features**

1. **Bonus Functionality**:
    - Use **only one static variable** to handle multiple file descriptors.
    - Manage independent read states for each descriptor, allowing `get_next_line` to switch between descriptors without mixing states.
2. **Testing for Bonus Functionality**:
    - Create a test suite with multiple file descriptors read in varying orders.
    - Check for consistency in reading from each descriptor and the correct handling of each read thread without leaks or overlaps.

**Estimated Time**: 10-12 hours

---

### **Phase 5: Code Quality, Optimization, and Norm Compliance**

1. **Norm Compliance**:
    - Ensure the code adheres to the 42 Norm with no errors (functions under 25 lines, indentation, naming conventions).
2. **Memory and Performance Optimization**:
    - Refactor utility functions to minimize repeated code and enhance readability.
    - Optimize reading logic to avoid unnecessary `read()` calls.
3. **Final Testing**:
    - Re-run all tests with edge cases on different buffer sizes.
    - Check against the 42 Norm using `norminette`.

**Estimated Time**: 8 hours

---

## **Total Estimated Time**

| Phase | Estimated Hours |
| --- | --- |
| Phase 1: Preparation & Planning | 5 |
| Phase 2: Core Implementation | 10 |
| Phase 3: Core Testing & Debugging | 8 |
| Phase 4: Bonus Implementation | 10-12 |
| Phase 5: Code Quality & Norm Compliance | 8 |

**Total Estimated Hours**: **41-43 hours**

---

This roadmap covers each element of `get_next_line` with targeted time estimates and clear milestones. Stick to each phase, focus on modular code, and ensure rigorous testing, especially around edge cases and file descriptor management for bonus points. This should yield a well-tested and Norm-compliant solution for the project.

---

