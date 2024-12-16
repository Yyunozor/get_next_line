NAME = $(LIB_DIR)/libgnl.a  # Changed from get_next_line.a to follow standard library naming
TEST = test_gnl
MAIN = main_gnl

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
AR = ar rcs

# Directories
TEST_DIR = TESTS
OBJ_DIR = $(TEST_DIR)/obj
LIB_DIR = $(TEST_DIR)/lib

# Source files
SRCS = get_next_line.c get_next_line_utils.c
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

# Object files with path
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

# Library with path
NAME = $(LIB_DIR)/libgnl.a

# Test files
TEST_SRC = $(TEST_DIR)/test_gnl.c
MAIN_SRC = $(TEST_DIR)/main_GNL.c

# Buffer size can be set via command line: make BS=42
BS ?= 32
BUFFER_SIZE = $(BS)

# Test file configuration
TEST_FILE ?= TEXTS_TO_GNL/test.txt   # Default test file for both main and test targets

# Create directories if they don't exist
DIRS = $(TEST_DIR) TEXTS_TO_GNL $(OBJ_DIR) $(LIB_DIR)

all: mkdirs $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

# Update object compilation rule
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

# Move mkdirs rule before it's used
mkdirs:
	@mkdir -p $(DIRS)
	@if [ ! -f $(TEST_FILE) ]; then \
		echo "This is a test file\nWith multiple lines\nFor testing get_next_line" > $(TEST_FILE); \
	fi

# Test executables
TEST = test_gnl
MAIN = main_gnl
BATTLE = battle_tester

# Test source files
TEST_SRC = $(TEST_DIR)/test_gnl.c
MAIN_SRC = $(TEST_DIR)/main_GNL.c
BATTLE_SRC = $(TEST_DIR)/battle_test.c

# Compilation flags
TEST_FLAGS = -L$(LIB_DIR) -lgnl

# Test targets
test: test_basic test_main test_battle

test_basic: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(TEST_SRC) $(TEST_FLAGS) -o $(TEST)
	@echo "\n=== Running Basic Tests ==="
	@./$(TEST) $(TEST_FILE)

test_main: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(MAIN_SRC) $(TEST_FLAGS) -o $(MAIN)
	@echo "\n=== Running Main Tests ==="
	@./$(MAIN) $(TEST_FILE)

test_battle: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(BATTLE_SRC) $(TEST_FLAGS) -o $(BATTLE)
	@echo "\n=== Running Battle Tests ==="
	@./$(BATTLE)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TEST) $(MAIN) $(BATTLE)

fclean: clean
	rm -f $(NAME)
	rm -rf $(DIRS)

re: fclean all

# Additional test targets with different buffer sizes
test1: clean
	@make test BS=1 TEST_FILE=$(TEST_FILE)

test42: clean
	@make test BS=42 TEST_FILE=$(TEST_FILE)

test9999: clean
	@make test BS=9999 TEST_FILE=$(TEST_FILE)

# Battle test targets
battle: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(TEST_DIR)/battle_test.c -L$(LIB_DIR) -lgnl -o battle_tester
	@echo "\n=== Running Comprehensive Battle Tests ==="
	@./battle_tester

battle_basic: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(TEST_DIR)/battle_test.c $(NAME) -o battle_tester
	@echo "\n=== Running Basic Test ==="
	@./battle_tester TEXTS_TO_GNL/1.txt

battle_unicode: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(TEST_DIR)/battle_test.c $(NAME) -o battle_tester
	@echo "\n=== Running Unicode Test ==="
	@./battle_tester TEXTS_TO_GNL/2.txt

battle_stress: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(TEST_DIR)/battle_test.c $(NAME) -o battle_tester
	@echo "\n=== Running Stress Test ==="
	@./battle_tester TEXTS_TO_GNL/3.txt

battle_large: mkdirs $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BS) $(TEST_DIR)/battle_test.c $(NAME) -o battle_tester
	@echo "\n=== Running Large File Test ==="
	@./battle_tester TEXTS_TO_GNL/bible.txt

# Update test_all to use different buffer sizes
test_all: fclean
	@echo "Running comprehensive tests with multiple buffer sizes..."
	@make battle BS=1
	@make battle BS=42
	@make battle BS=9999

.PHONY: all bonus clean fclean re test test_basic test_main test_battle mkdirs battle battle_basic battle_unicode battle_stress battle_large test_all
