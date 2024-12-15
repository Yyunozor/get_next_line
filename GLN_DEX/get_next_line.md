# **get_next_line.c**

---

### **Purpose**:

The `get_next_line.c` file implements the `get_next_line` function and its helper functions. Its purpose is to read a single line from a file descriptor, ensuring efficient memory usage, and proper handling of multi-line text files.

---

### **Key Functions**:

1. **`get_line_from_buffer`**
2. **`create_new_buffer`**
3. **`update_buffer`**
4. **`read_buffer`**
5. **`get_next_line`**

Each function contributes to reading, extracting, and updating the buffer to facilitate efficient line-by-line reading.

---

## **Function 1: `get_line_from_buffer`**

---

### **Purpose**:

Extracts the next complete line from the buffer.

---

### **Prototype**:

```c
static char	*get_line_from_buffer(char *buffer);

```

---

### **Input**:

- `buffer`: The current content stored in the static buffer.

---

### **Output**:

- A dynamically allocated string containing the next line from the buffer.
- Returns `NULL` if the buffer is empty or allocation fails.

---

### **Explanation**:

1. **Locate Line End**:
    - Searches for the next `'\n'` or the end of the string.
2. **Calculate Line Length**:
    - Determines the length of the line including the `'\n'` (if present).
3. **Allocate and Copy**:
    - Allocates memory for the line and copies characters until the newline or buffer end.

---

### **Edge Cases**:

- Empty buffer or `NULL` → Returns `NULL`.
- Memory allocation fails → Returns `NULL`.

---

## **Function 2: `create_new_buffer`**

---

### **Purpose**:

Creates a new buffer by removing the extracted line from the old buffer.

---

### **Prototype**:

```c
static char	*create_new_buffer(char *buffer, char *newline_pos);

```

---

### **Input**:

- `buffer`: The current buffer.
- `newline_pos`: Pointer to the newline character in the buffer.

---

### **Output**:

- Returns a new buffer containing the remaining content after the extracted line.
- Frees the old buffer.

---

### **Explanation**:

1. **Allocate Memory**:
    - Allocates enough space for the remaining content.
2. **Copy Remaining Content**:
    - Copies characters from the old buffer after the newline into the new buffer.
3. **Free Old Buffer**:
    - Frees the old buffer to avoid memory leaks.

---

### **Edge Cases**:

- No remaining content → Returns `NULL`.
- Allocation fails → Frees the old buffer and returns `NULL`.

---

## **Function 3: `update_buffer`**

---

### **Purpose**:

Updates the buffer by removing the already-read line.

---

### **Prototype**:

```c
static char	*update_buffer(char *buffer);

```

---

### **Input**:

- `buffer`: The current buffer.

---

### **Output**:

- Returns the updated buffer with the remaining content.
- Frees the buffer if no content remains.

---

### **Explanation**:

1. **Locate Newline**:
    - Finds the position of the newline in the buffer.
2. **Handle Remaining Content**:
    - Calls `create_new_buffer` to create a new buffer with the remaining content.
3. **Free and Return**:
    - Frees the old buffer if no content remains.

---

### **Edge Cases**:

- No newline → Frees the buffer and returns `NULL`.

---

## **Function 4: `read_buffer`**

---

### **Purpose**:

Reads data from the file descriptor and appends it to the buffer until a newline or EOF is found.

---

### **Prototype**:

```c
static char	*read_buffer(int fd, char *buffer);

```

---

### **Input**:

- `fd`: File descriptor to read from.
- `buffer`: Current buffer content.

---

### **Output**:

- Returns an updated buffer with the new content appended.
- Frees the buffer if an error occurs.

---

### **Explanation**:

1. **Allocate Temporary Buffer**:
    - Allocates memory to temporarily store data read from `fd`.
2. **Read Until Newline or EOF**:
    - Reads data in chunks of `BUFFER_SIZE` until a newline or EOF is encountered.
3. **Append to Static Buffer**:
    - Uses `ft_strjoin` to append the new data to the buffer.

---

### **Edge Cases**:

- Memory allocation fails → Frees buffer and returns `NULL`.
- Read error → Frees buffer and returns `NULL`.

---

## **Function 5: `get_next_line`**

---

### **Purpose**:

Reads a single line from a file descriptor, leveraging the static buffer for efficient memory management.

---

### **Prototype**:

```c
char	*get_next_line(int fd);

```

---

### **Input**:

- `fd`: The file descriptor to read from.

---

### **Output**:

- Returns a dynamically allocated string containing the next line.
- Returns `NULL` if:
    - End of file is reached.
    - An error occurs.
    - Memory allocation fails.

---

### **Explanation**:

1. **Validate Input**:
    - Checks if `fd` and `BUFFER_SIZE` are valid.
2. **Read Data**:
    - Calls `read_buffer` to ensure the buffer contains data.
3. **Extract Line**:
    - Calls `get_line_from_buffer` to extract the next line from the buffer.
4. **Update Buffer**:
    - Updates the buffer by removing the extracted line.

---

### **Edge Cases**:

- Invalid `fd` → Returns `NULL`.
- Empty file → Returns `NULL`.
- Memory allocation failure → Returns `NULL`.

---

### **Visual Focus**

### Before Reading:

Buffer: `NULL`

### During Execution:

1. Read content into the buffer: `"Hello\nWorld\n42"`.
2. Extract `"Hello\n"` as the first line.

### After Execution:

| Function Call | Returned Line | Remaining Buffer |
| --- | --- | --- |
| 1 | `"Hello\n"` | `"World\n42"` |
| 2 | `"World\n"` | `"42"` |
| 3 | `"42"` | (Empty) |
| 4 | `NULL` | (Empty) |

---

### **Conclusion**:

The `get_next_line.c` implementation efficiently reads lines from a file descriptor by:

- Using a static buffer to manage state across multiple calls.
- Handling memory allocation and errors gracefully.
- Providing reusable helper functions for modularity.

---
