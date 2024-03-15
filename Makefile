# C++ compiler flags.
CXXFLAGS = -Wall -O3 -fPIC

# Libraries.
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Source directory.
SRC_DIR = src

# Source files.
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Object directory.
OBJ_DIR = build

# Object files.
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Implicit rule to compile.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# Phony targets.
.PHONY: all rm headers

# Default target.
all: $(OBJ_DIR)/libDPGE.so $(OBJ_DIR)/libDPGE.a headers

# Shared library.
$(OBJ_DIR)/libDPGE.so: $(OBJ_FILES)
	$(CXX) -shared $(OBJ_FILES) -o $@ $(LDLIBS)

# Static library.
$(OBJ_DIR)/libDPGE.a: $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)

# Make headers directory
headers:
	mkdir -p include/DPGE
	cp $(SRC_DIR)/*.hpp include/DPGE/

# Copy the headers in a directory.
$(OBJ_DIR)/DPGE: $(wildcard $(SRC_DIR/*.hpp))
	mkdir -p build/DPGE
	cp $(SRC_DIR)/*.hpp $(OBJ_DIR)/DPGE

# Documentation.
doc: Doxyfile
	doxygen $^

# Phony targets to remove object files.
.PHONY: rm

# Remove all the object files.
rm:
	rm -rf build/*.o build/DPGE.so build/headers
