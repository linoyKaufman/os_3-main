CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: deque_graph list_graph

deque_graph: main.cpp deque_graph.o graph.o
	$(CXX) $(CXXFLAGS) -DUSE_DEQUE -o deque_graph main.cpp deque_graph.o graph.o

list_graph: main.cpp list_graph.o graph.o
	$(CXX) $(CXXFLAGS) -DUSE_LIST -o list_graph main.cpp list_graph.o graph.o

deque_graph.o: deque_graph.cpp deque_graph.hpp
	$(CXX) $(CXXFLAGS) -DUSE_DEQUE -c deque_graph.cpp

list_graph.o: list_graph.cpp list_graph.hpp
	$(CXX) $(CXXFLAGS) -DUSE_LIST -c list_graph.cpp

graph.o: graph.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

clean:
	rm -f deque_graph list_graph *.o
