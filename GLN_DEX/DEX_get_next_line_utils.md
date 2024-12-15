# **get_next_line_utils.c**

---

### **Purpose**:

The `get_next_line_utils.c` file contains helper functions that are used to support the main `get_next_line`functionality. These utility functions handle common tasks such as calculating string lengths, finding characters in a string, joining strings, and safely freeing memory.

---

### **Key Functions**:

1. **`ft_strlen`**: Calculates the length of a string.
2. **`ft_strchr`**: Locates the first occurrence of a character in a string.
3. **`ft_strjoin`**: Concatenates two strings into a new dynamically allocated string.
4. **`free_null`**: Frees memory and returns `NULL` for safety.

---

## **Function 1: `ft_strlen`**

---

### **Purpose**:

Calculates the length of a given string.

---

### **Prototype**:

```c
size_t	ft_strlen(const char *s);

```

---

### **Input**:

- `s`: The input string.

---

### **Output**:

- Returns the number of characters in the string (excluding the null-terminator).
- Returns `0` if the input string is `NULL`.

---

### **Code Implementation**:

```c
size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	if (!s)
		return (0);
	ptr = s;
	while (*ptr)
		ptr++;
	return (ptr - s);
}

```

---

### **Explanation**:

1. **Null Check**:
    - If the input string `s` is `NULL`, returns `0`.
2. **Count Characters**:
    - Uses a pointer to iterate through the string until the null-terminator (`'\0'`) is found.
3. **Calculate Length**:
    - Returns the difference between the starting pointer and the current pointer position.

---

### **Edge Cases**:

- **NULL Input**: Returns `0`.

---

## **Function 2: `ft_strchr`**

---

### **Purpose**:

Locates the first occurrence of a character in a string.

---

### **Prototype**:

```c
char	*ft_strchr(const char *s, int c);

```

---

### **Input**:

- `s`: The input string.
- `c`: The character to locate.

---

### **Output**:

- Returns a pointer to the first occurrence of the character `c` in the string `s`.
- Returns `NULL` if the character is not found.

---

### **Code Implementation**:

```c
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

```

---

### **Explanation**:

1. **Null Check**:
    - If the input string `s` is `NULL`, returns `NULL`.
2. **Search for Character**:
    - Iterates through the string, comparing each character to `c`.
    - Returns a pointer to the first matching character.
3. **Handle Null-Terminator**:
    - If `c` is `'\0'`, returns a pointer to the end of the string.

---

### **Edge Cases**:

- **NULL Input**: Returns `NULL`.
- **Search for Null-Terminator**: Returns a pointer to the end of the string.

---

## **Function 3: `ft_strjoin`**

---

### **Purpose**:

Concatenates two strings into a new dynamically allocated string.

---

### **Prototype**:

```c
char	*ft_strjoin(char *s1, const char *s2);

```

---

### **Input**:

- `s1`: The first string.
- `s2`: The second string.

---

### **Output**:

- Returns a pointer to the newly allocated string containing `s1` followed by `s2`.
- Returns `NULL` if memory allocation fails.

---

### **Code Implementation**:

```c
char	*ft_strjoin(char *s1, const char *s2)
{
	char	*str;
	char	*ptr;
	char	*tmp;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	ptr = str;
	if (s1)
	{
		tmp = s1;
		while (*tmp)
			*ptr++ = *tmp++;
	}
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	if (s1)
		free(s1);
	return (str);
}

```

---

### **Explanation**:

1. **Calculate Total Length**:
    - Computes the total length of `s1` and `s2` to allocate memory for the new string.
2. **Memory Allocation**:
    - Allocates memory for the concatenated string, including space for the null-terminator.
3. **Copy Strings**:
    - Copies characters from `s1` and `s2` into the newly allocated string.
4. **Free First String**:
    - Frees `s1` after concatenation to avoid memory leaks.

---

### **Edge Cases**:

- **NULL Inputs**:
    - If `s1` is `NULL`, only `s2` is copied.
    - If `s2` is `NULL`, only `s1` is copied.
- **Memory Allocation Failure**:
    - Returns `NULL`.

---

## **Function 4: `free_null`**

---

### **Purpose**:

Frees memory pointed to by `ptr` and returns `NULL`.

---

### **Prototype**:

```c
char	*free_null(void *ptr);

```

---

### **Input**:

- `ptr`: Pointer to the memory to be freed.

---

### **Output**:

- Always returns `NULL`.

---

### **Code Implementation**:

```c
char	*free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

```

---

### **Explanation**:

1. **Null Check**:
    - Frees the memory if `ptr` is not `NULL`.
2. **Return Value**:
    - Always returns `NULL` to standardize behavior.

---

### **Edge Cases**:

- **NULL Input**:
    - Does nothing and simply returns `NULL`.

---

### **Conclusion**:

The utility functions in `get_next_line_utils.c`:

- Provide efficient implementations for common string and memory operations.
- Enhance modularity and code readability by abstracting helper tasks.
- Handle memory allocation and deallocation gracefully to prevent leaks.