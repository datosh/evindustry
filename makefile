# specify the compiler
CXX=clang++

# specify compiler flags
CXXFLAGS=-std=c++11 -lyaml-cpp

# specify the target
all: main

main: src/main.cpp src/blueprint.hpp src/parsing_structs.hpp src/item.hpp
	$(CXX) src/main.cpp $(CXXFLAGS) -o main

dbg: src/main.cpp src/blueprint.hpp src/parsing_structs.hpp src/item.hpp
	$(CXX) src/main.cpp $(CXXFLAGS) -g -o main