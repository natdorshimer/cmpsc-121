# Detect the operating system
ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

# Set compiler based on the detected operating system
ifeq ($(detected_OS), Windows)
    CXX := g++
else
    CXX := $(shell command -v clang++ 2> /dev/null || echo g++)
endif

# Directories
SRC_DIR := $(TARGET)/src
BUILD_DIR := $(TARGET)/build

# Source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Target binary
TARGET_BIN := $(BUILD_DIR)/$(TARGET)

# Targets
.PHONY: all run clean

all: $(TARGET_BIN)

run: all
	@./$(TARGET_BIN)

clean:
	rm -rf $(BUILD_DIR)

$(TARGET_BIN): $(OBJ_FILES)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) -c $< -o $@