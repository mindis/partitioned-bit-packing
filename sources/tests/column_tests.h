#ifndef COLUMN_TESTS_H_
#define COLUMN_TESTS_H_

#include "database/Column.h"
#include "vectors/BasicBitPackedVector.h"
#include "vectors/DynamicBitPackedVector.h"
#include "vectors/PartitionedBitPackedVectors.h"

bool abstract_column_test(const char* test_name, AbstractColumn<long>* v, size_t distinct_values, bool expect_fail = false) {
    const size_t num_elements = 10000;

    long data[num_elements];
    for (size_t n = 0; n < num_elements; ++n) {
        data[n] = rand() % distinct_values;
        v->push_back(data[n]);
    }

    bool ok = true;
    for (size_t n = 0; n < num_elements; ++n) {
        if (data[n] != v->get(n)) {
            if (!expect_fail) printf("Error: Pos %lu, Expected %ld, Got %ld\n", n, data[n], v->get(n));
            ok = false;
            break;
        }
    }

    delete v;

    ok = (expect_fail && !ok) || (!expect_fail && ok);
    if (ok) printf("Abstract Column Test passed: %s\n", test_name);
    else printf("Abstract Column Test failed: %s\n", test_name);
    return ok;
}



bool run_column_tests() {
    bool ok = true;

    abstract_column_test("BPV", new Column<BasicBitPackedVector, long>(8), 200);
    abstract_column_test("D-BPV", new Column<DynamicBitPackedVector, long>(2), 200);
    abstract_column_test("Basic-Partitioned", new Column<BasicPartitionedVector, long>(2), 200);
    abstract_column_test("Partitioned Get 1", new Column<PartitionedBitPackedVector_Get_1, long>(2), 200);
    abstract_column_test("Partitioned Get 2", new Column<PartitionedBitPackedVector_Get_2, long>(2), 200);
    abstract_column_test("Partitioned Get 3", new Column<PartitionedBitPackedVector_Get_3, long>(2), 200);

    if (ok) printf("All column tests passed!\n\n");
    else printf("Some column tests failed!\n\n");
    return ok;
}

#endif