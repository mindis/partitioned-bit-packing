#ifndef GET_BENCHMARKS_H_
#define GET_BENCHMARKS_H_


#include "benchmark/Benchmarker.h"
#include "benchmark/PapiTimer.h"

#include "vectors/BitPackedVectorSIMD.h"
#include "vectors/PartitionedVectorTemplate.h"
#include "vectors/PartitionedBitPackedVectors.h"

#include "operations/EqScanOp.h"

#include "database/Dictionary.h"

#include "utils/utils.h"
#include "utils/data_generation.h"


class ScanBenchmarker : public NumericBenchmarker<double> {
public:
    size_t _num_elements, _distinct_values;
    uint** _data;
    ScanBenchmarker(uint runs, size_t numElements, size_t distinctValues, uint** data) : NumericBenchmarker<double>(runs) {
        _data = data;
        _num_elements = numElements;
        _distinct_values = distinctValues;
    }


    double run() {
        return run(_data[_run_nr], _num_elements, _distinct_values);
    }
    virtual double run(uint* data, uint num_elements, uint distinct_values) = 0;
};



class BaseSIMDScanBenchmarker : public ScanBenchmarker {
public:
    BaseSIMDScanBenchmarker(uint r, size_t n, size_t dv, uint** data) : ScanBenchmarker(r, n, dv, data) {}

    double run(uint* data, uint num_elements, uint distinct_values) {
        BitPackedVectorSIMD v(bitsNeeded(distinct_values));
        EqScanOp<BitPackedVectorSIMD> scan_op(&v);

        for (size_t n = 0; n < num_elements; ++n) v.push_back(data[n]);

        PAPIClockCycleTimer timer(true);
        scan_op.scan(10);
        timer.stop();

        // Sanity check
        for (size_t n = 0; n < num_elements; ++n) {
            if (v.get(n) != data[n]) printf("Error 2: There was an error in the benchmark. %lu\n", scan_op.matches());
        }

        return timer.result() / num_elements;
    }
};


class PartitionedSIMDScanBenchmarker : public ScanBenchmarker {
public:
    PartitionedSIMDScanBenchmarker(uint r, size_t n, size_t dv, uint** data) : ScanBenchmarker(r, n, dv, data) {}

    double run(uint* data, uint num_elements, uint distinct_values) {
        uint* encoded = new uint[num_elements];
        Dictionary<uint> dict = Dictionary<uint>(1);
        PartitionedVectorTemplate<BitPackedVectorSIMD> v(1);
        EqPartitionedScanOp<PartitionedVectorTemplate<BitPackedVectorSIMD>, BitPackedVectorSIMD> scan_op(&v);

        for (size_t n = 0; n < num_elements; ++n) {
            encoded[n] = dict.encode(data[n]);
            v.setEncodingBits(dict.getBits());
            v.push_back(encoded[n]);
        }


        PAPIClockCycleTimer timer(true);
        scan_op.scan(10);
        timer.stop();


        // Sanity check
        for (size_t n = 0; n < num_elements; ++n) {
            if (v.get(n) != encoded[n]) printf("Error 2: There was an error in the benchmark. %lu\n", scan_op.matches());
        }

        delete[] encoded;
        return timer.result() / num_elements;
    }
};

class DynamicSIMDScanBenchmarker : public ScanBenchmarker {
public:
    DynamicSIMDScanBenchmarker(uint r, size_t n, size_t dv, uint** data) : ScanBenchmarker(r, n, dv, data) {}

    double run(uint* data, uint num_elements, uint distinct_values) {
        uint* encoded = new uint[num_elements];
        Dictionary<uint> dict = Dictionary<uint>(1);
        DynamicBitPackedVectorSIMD v(1);
        EqScanOp<DynamicBitPackedVectorSIMD> scan_op(&v);

        for (size_t n = 0; n < num_elements; ++n) {
            encoded[n] = dict.encode(data[n]);
            v.setEncodingBits(dict.getBits());
            v.push_back(encoded[n]);
        }

        PAPIClockCycleTimer timer(true);
        scan_op.scan(10);
        timer.stop();

        // Sanity check
        for (size_t n = 0; n < num_elements; ++n) {
            if (v.get(n) != encoded[n]) printf("Error 2: There was an error in the benchmark. %lu\n", scan_op.matches());
        }

        delete[] encoded;
        return timer.result() / num_elements;
    }
};




void run_scan_benchmarks() {
	printf("Scan Benchmark\n");

    const uint runs = 5;

    printf("Size,DV,Base,Partitioned,Dynamic\n");
    for (ulong num_elements = 100000; num_elements <= 10000000; num_elements *= 1.5) {
        ulong distinct_values = num_elements * 0.10;

        uint* data[runs];
        for (uint n = 0; n < runs; ++n) {
            data[n] = UniformGenerator::multiple(1, distinct_values, num_elements);
        }
        
        //BaselineInsertBenchmarker b1(runs, num_elements, distinct_values, data);
        // b1.runBenchmark();

        BaseSIMDScanBenchmarker b2(runs, num_elements, distinct_values, data);
        b2.runBenchmark();

        PartitionedSIMDScanBenchmarker b3(runs, num_elements, distinct_values, data);
        b3.runBenchmark();

        DynamicSIMDScanBenchmarker b4(runs, num_elements, distinct_values, data);
        b4.runBenchmark();



        printf("%lu,%lu,%.2f,%.2f,%.2f\n",
            num_elements,
            distinct_values,
            b2.avg(), b3.avg(), b4.avg());
    }
}


#endif