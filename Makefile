.PHONY: all bstree clean

all: bstree

bstree:
	g++ -std=c++11 -o main BSTree.cpp Node.cpp main.cpp

clean:
	rm ./main
