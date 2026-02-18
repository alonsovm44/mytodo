# GLUPE_BLOCK_START: Makecmd

# Target name: mytodo
# Compile main.cpp with g++ -std=c++17 -static

CXX = g++
CXXFLAGS = -std=c++17 -static
TARGET = mytodo

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

# GLUPE_BLOCK_END: Makecmd
