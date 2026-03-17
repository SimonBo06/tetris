# Compiler and flags  
CC = g++  
CFLAGS = -Wall -Wextra -g -MMD -MP  # -MMD -MP for dependency generation  
LDFLAGS =  

# Directories  
SRC_DIR = src
INCLUDE_DIR =include
BUILD_DIR =build
BIN_DIR =bin
TARGET =$(BIN_DIR)/snake

# Include paths  
INCLUDES = -I$(INCLUDE_DIR)
# Find all .cpp files  
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

# Generate object file paths  
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Auto-generated dependency files  
DEPS := $(OBJECTS:.o=.d)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Build executable  
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)
	@echo "Built target: $@"

# Compile .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean artifacts
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned build and bin directories"

# Include dependencies
-include $(DEPS)