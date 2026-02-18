# GLUPE_BLOCK_START: Makecmd
all: mytodo

mytodo: main.cpp
	g++ -std=c++17 -static -o mytodo main.cpp

clean:
	rm -f mytodo todo.txt
# GLUPE_BLOCK_END: Makecmd
