#ifndef VECTOR_TESTS_H_
#define VECTOR_TESTS_H_

#include "vectors/AbstractBitPackedVector.h"
#include "vectors/BasicBitPackedVector.h"
#include "vectors/DynamicBitPackedVector.h"
#include "vectors/BasicPartitionedVector.h"
#include "vectors/PartitionedBitPackedVectors.h"


bool abstract_vector_test(const char* test_name, AbstractBitPackedVector* v, size_t distinct_values, bool expect_ok = true) {
    const size_t num_elements = 10000;

    uint data[num_elements];
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
        v->push_back(data[n]);
    }

    bool ok = true;
    for (size_t n = 0; n < num_elements; ++n) {
        if (data[n] != v->get(n)) {
            if (expect_ok) printf("Error: Pos %lu, Expected %u, Got %u\n", n, data[n], v->get(n));
            ok = false;
            break;
        }
    }

	delete v;
    ok = (expect_ok && ok) || (!expect_ok && !ok);
    if (ok) printf("Abstract Vector Test passed: %s\n", test_name);
    else printf("Abstract Vector Test failed: %s\n", test_name);
    return ok;
}

bool dynamic_vector_test(const char* test_name, AbstractBitPackedVector* v) {
    const size_t num_elements = 10000;
    uint data[num_elements];

    v->setEncodingBits(10);
    for (size_t n = 0; n < num_elements / 2; ++n) {
        data[n] = rand() % 1000;
        v->push_back(data[n]);
    }

    v->setEncodingBits(14);
    for (size_t n = 0; n < num_elements / 2; ++n) {
        size_t i = n + num_elements / 2;
        data[i] = rand() % 8000;
        v->push_back(data[i]);
    }

    bool ok = true;
    for (size_t n = 0; n < num_elements; ++n) {
        if (data[n] != v->get(n)) {
            printf("Error: Pos %lu, Expected %u, Got %u\n", n, data[n], v->get(n));
            ok = false;
            break;
        }
    }

	delete v;
    if (ok) printf("Dynamic Vector Test passed: %s\n", test_name);
    else printf("Dynamic Vector Test failed: %s\n", test_name);
    return ok;
}



bool run_vector_tests() {
    bool ok = true;
    ok &= abstract_vector_test("BPV (1)", new BasicBitPackedVector(4), 10);
    ok &= abstract_vector_test("BPV (2)", new BasicBitPackedVector(10), 1000);
    ok &= abstract_vector_test("BPV (3)", new BasicBitPackedVector(6), 1000, false);
    ok &= abstract_vector_test("BPV (4)", new BasicBitPackedVector(24), 1000000);
    ok &= abstract_vector_test("D-BPV (1)", new DynamicBitPackedVector(10), 1000);
    ok &= abstract_vector_test("P-BPV (1)", new BasicPartitionedVector(14), 10000);
    ok &= dynamic_vector_test("D-BPV (1)", new DynamicBitPackedVector(10));
    ok &= dynamic_vector_test("Basic-Partitioned", new BasicPartitionedVector(5));
    ok &= dynamic_vector_test("Partitioned Get 1", new PartitionedBitPackedVector_Get_1(5));
    ok &= dynamic_vector_test("Partitioned Get 2", new PartitionedBitPackedVector_Get_2(5));
    ok &= dynamic_vector_test("Partitioned Get 3", new PartitionedBitPackedVector_Get_3(5));

    if (ok) printf("All vector tests passed!\n\n");
    else printf("Some vector tests failed!\n\n");
    return ok;
}

#endif