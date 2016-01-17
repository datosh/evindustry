# specify the compiler
CXX=clang++

# specify compiler flags
CXXFLAGS=-std=c++11 -lyaml-cpp

# specify the target
all: main.elf

main.elf: src/main.cpp
	$(CXX) src/main.cpp $(CXXFLAGS) -o main.elf