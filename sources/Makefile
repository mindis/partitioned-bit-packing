
USE_PAPI := 0
USE_BCV := 1


CXX = g++
INCLUDES = -I./lib/ -I./ -I/lib/bcv/pkg/
LIBS = 
CFLAGS = -std=c++0x -O3 -mssse3 -msse4.1 -Wall

TARGET = ./partitionedvector
OBJ = main.o lib/vectors/BasicBitPackedVector.o lib/vectors/BasicPartitionedVector.o lib/vectors/DynamicBitPackedVector.o lib/vectors/PartitionedVectorSIMD.o lib/utils/data_generation.o



ifeq ($(USE_PAPI),1)
    LIBS += -lpapi
    CFLAGS += -D WITH_PAPI
endif

ifeq ($(USE_BCV),1)
    CFLAGS += -D WITH_BCV -Wno-unused-variable -Wno-reorder
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
