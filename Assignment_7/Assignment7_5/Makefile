# Compiler and Flags
CC = gcc
CFLAGS = -Wall -fPIC -Iinclude
LDFLAGS = -shared

# Directories
SRC_DIR = src
INC_DIR = include
LIB_DIR = .

# Target Library Names
LIB_STRING = libmystring.so
LIB_MATH = libmymath.so
TARGET = my_app

# Source Files
SRCS_STRING = $(SRC_DIR)/mystring.c
SRCS_MATH = $(SRC_DIR)/mymath.c

# Object Files
OBJS_STRING = $(SRCS_STRING:.c=.o)
OBJS_MATH = $(SRCS_MATH:.c=.o)

# Default Rule
all: $(LIB_STRING) $(LIB_MATH) $(TARGET)

# Rule to create the String Shared Library
$(LIB_STRING): $(OBJS_STRING)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Built $@"

# Rule to create the Math Shared Library
$(LIB_MATH): $(OBJS_MATH)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Built $@"

# Rule to compile Object Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile the Client Application
$(TARGET): main.c
	$(CC) main.c -L$(LIB_DIR) -lmystring -lmymath -I$(INC_DIR) -o $(TARGET)
	@echo "Successfully compiled $(TARGET)"

# Clean up build files
clean:
	rm -f $(SRC_DIR)/*.o $(LIB_DIR)/*.so $(TARGET)
	@echo "Cleanup complete."

# Run the application (sets library path automatically)
run:
	LD_LIBRARY_PATH=$(LIB_DIR) ./$(TARGET)