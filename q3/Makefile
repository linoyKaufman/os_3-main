CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra


TARGET = main


SRCS = main.cpp deque_graph.cpp
OBJS = $(SRCS:.cpp=.o)


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)


main.o: main.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

deque_graph.o: deque_graph.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c deque_graph.cpp


clean:
	rm -f $(TARGET) $(OBJS)

