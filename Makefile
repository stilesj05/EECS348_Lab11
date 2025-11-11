CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OBJ = main.o Matrix.o

all: lab11

lab11: $(OBJ)
	$(CXX) $(CXXFLAGS) -o lab11 $(OBJ)

clean:
	rm -f *.o lab11
