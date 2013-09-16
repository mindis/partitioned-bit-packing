
CXX = g++
INCLUDES = -I./lib/ -I./
LIBS = 
CFLAGS = -std=c++0x -O3 -Wall -mssse3 -msse4.1

TARGET = ./partitionedvector
OBJ = main.o lib/vectors/BasicBitPackedVector.o lib/vectors/BasicPartitionedVector.o lib/vectors/DynamicBitPackedVector.o

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS += -lpapi
endif


all: run

run: productive
	$(TARGET)

productive: build
debug: CXX += -g
debug: build

valgrind: debug
	valgrind --leak-check=full $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)

build: _build_no_clean
	rm -f $(OBJ)

_build_no_clean: $(OBJ)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDES)
