# Define the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -O3 -I/usr/include 

# Linker flags
LDFLAGS =  -lgsl -lgslcblas -lm

# Define home directory
HOME = ~

# Define the output file
TARGET = cleavagesim.out

# Source files
SOURCES = main_cleavagesim.cpp cleavagesim.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link the target with object files
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJECTS)

# Dummy targets
.PHONY: all clean
