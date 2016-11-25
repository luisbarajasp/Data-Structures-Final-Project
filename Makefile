#Variables
CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = main.o
DEPS = Edge.hpp Graph.hpp InfoNode.hpp LinkedList.hpp Node.hpp Queue.hpp Stack.hpp Vertex.hpp

# Basic rule to compile the program
graphs: $(OBJECTS)
	$(CXX) $^ -o $(@) $(CXXFLAGS) $(LDFLAGS)

# Basic rule to compile the program
%.o: %.cpp $(DEPS)
	$(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS) -c

clean:
	-rm -f graphs *.o

.PHONY: clean
