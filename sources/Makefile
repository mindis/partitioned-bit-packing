
USE_PAPI := 1
USE_BCV := 1


CXX = g++
INCLUDES = -I./lib/ -I./ -I/lib/bcv/pkg/
LIBS = 
CFLAGS = -std=c++0x -O3 -mssse3 -msse4.1 -Wall

LIB_OBJ = lib/vectors/BasicBitPackedVector.o lib/vectors/BasicPartitionedVector.o lib/vectors/DynamicBitPackedVector.o lib/vectors/PartitionedVectorSIMD.o lib/utils/data_generation.o

TEST_TARGET = ./libtest
TEST_OBJ = $(LIB_OBJ) main.o 

BENCHMARK_TARGET = ./benchmark
BENCHMARK_OBJ = $(LIB_OBJ) benchmark.o


ifeq ($(USE_PAPI),1)
    LIBS += -lpapi
    CFLAGS += -D WITH_PAPI
endif

ifeq ($(USE_BCV),1)
    CFLAGS += -D WITH_BCV -Wno-unused-variable -Wno-reorder -Wno-unused-result
endif







all: test

clean:
	rm -f $(TEST_TARGET)
	rm -f $(BENCHMARK_TARGET)
	rm -f $(LIB_OBJ)
	rm -f $(BENCHMARK_OBJ)
	rm -f $(TEST_OBJ)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDES)



# Test Build
test: test_build
	$(TEST_TARGET)

test_build: _build_test_no_clean
	rm -f $(TEST_OBJ)

_build_test_no_clean: $(TEST_OBJ)
	$(CXX) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) $(LIBS)



# Benchmark Build
benchmark: build_benchmark
	$(BENCHMARK_TARGET)

build_benchmark: _build_benchmark_no_clean
	rm -f $(BENCHMARK_OBJ)

_build_benchmark_no_clean: $(BENCHMARK_OBJ)
	$(CXX) $(CFLAGS) -o $(BENCHMARK_TARGET) $(BENCHMARK_OBJ) $(LIBS)


# Debug Build
debug: CXX += -g
debug: test_build

valgrind: debug
	valgrind --leak-check=full $(TEST_TARGET)



