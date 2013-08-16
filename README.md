Partitioned Bit-Packed Vector
=======================

An implementation of a partitioned bit-packed vector is shown in this work. The partitioned bit-packed vector is an extension of the normal bit-packed vector. It aims to increase the flexibility of the data-structure while maintaining a high compression benefit and a fast access perfomance. Modern in-memory databases could benefit from this more flexible data structure.

In this repository you'll find implementations of a normal bit-packed vector and partitioned bit-packed vectors. Several different access algorithms have been implemented and evaluated. 

OS Support:
 * Linux (Build System: GCC)
 * Windows (Build System: Visual Studio)

Dependencies:
 * (Optional) PAPI (http://icl.cs.utk.edu/papi/) is recommended for benchmarking. The benchmarks can run without PAPI, but it is recommended to do benchmarks on a Linux-OS using PAPI to measure the performance.




Abstract
-------------------------
*Taken from my Bachelor's Thesis "Partitioned Bit-Packed Vectors for In-Memory Column Stores"*

In recent database development, in-memory databases have grown more and more in popularity. The hardware development of the past years has made it possible for databases to hold all of their data in main memory. Still, most applications on in-memory databases are latency-bound rather than compute-bound. Combining strong compression techniques and eﬃcient data structures is essential to fully utilize the hardware capabilities. A common data structure for eﬃcient storing is the bit-packed vector. The bit-packed vector uses a ﬁxed encoding length, which cannot be changed after initialization. Therefore it requires full re-initialization, when the encoding-length changes.

In this Thesis a new data structure is proposed. The partitioned bit-packed vector is an alternative to the regular bit-packed vector. In the partitioned bit-packed vector the encoding length of the stored elements can be increased dynamically. This eliminates the need for expensive re-initializations. In this Thesis it is shown how this new data structure works and its performance is evaluated. It is discussed what beneﬁts the partitioned bit-packed vector can bring to an in-memory databases, when replacing the regular bit-packed vector. The results of this Thesis suggest that this new data structure has the capabilities to improve the performance of existing in-memory column-stores for speciﬁc workloads.
