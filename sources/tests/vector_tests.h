#ifndef VECTOR_TESTS_H_
#define VECTOR_TESTS_H_

#include "vectors/AbstractBitPackedVector.h"
#include "vectors/BasicBitPackedVector.h"
#include "vectors/DynamicBitPackedVector.h"


bool abstract_vector_test(const char* test_name, AbstractBitPackedVector* v, size_t distinct_values, bool expect_fail = false) {
    const size_t num_elements = 10000;

    uint data[num_elements];
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
        v->push_back(data[n]);
    }

    bool ok = true;
    for (size_t n = 0; n < num_elements; ++n) {
        if (data[n] != v->get(n)) {
            if (!expect_fail) printf("Error: Pos %u, Expected %u, Got %u\n", n, data[n], v->get(n));
            ok = false;
            break;
        }
    }

    ok = (expect_fail && !ok) || (!expect_fail && ok);
    if (ok) printf("Abstract Vector Test passed: %s\n", test_name);
    else printf("Abstract Vector Test failed: %s\n", test_name);
    return ok;
}

bool dynamic_vector_test() {
    DynamicBitPackedVector v(10);

    const size_t num_elements = 10000;
    uint data[num_elements];

    for (size_t n = 0; n < num_elements / 2; ++n) {
        data[n] = rand() % 1000;
        v.push_back(data[n]);
    }

    v.setEncodingBits(14);
    for (size_t n = 0; n < num_elements / 2; ++n) {
        size_t i = n + num_elements / 2;
        data[i] = rand() % 8000;
        v.push_back(data[i]);
    }

    bool ok = true;
    for (size_t n = 0; n < num_elements; ++n) {
        if (data[n] != v.get(n)) {
            printf("Error: Pos %u, Expected %u, Got %u\n", n, data[n], v.get(n));
            ok = false;
            break;
        }
    }
    if (ok) printf("Dynamic Vector Test passed.\n");
    else printf("Dynamic Vector Test failed.\n");
    return ok;
}



bool run_vector_tests() {
    bool ok = true;
    ok &= abstract_vector_test("BPV Test 1", new BasicBitPackedVector(4), 10);
    ok &= abstract_vector_test("BPV Test 2", new BasicBitPackedVector(10), 1000);
    ok &= abstract_vector_test("BPV Test 3", new BasicBitPackedVector(6), 1000, true);
    ok &= abstract_vector_test("BPV Test 4", new BasicBitPackedVector(24), 1000000);
    ok &= abstract_vector_test("Dynamic BPV Test 1", new DynamicBitPackedVector(10), 1000);
    ok &= dynamic_vector_test();

    if (ok) printf("All vector tests passed!\n");
    else printf("Some vector tests failed!\n");
    return ok;
}

#endif