#ifndef PAPI_BENCHMARKER_H_
#define PAPI_BENCHMARKER_H_



#ifdef WITH_PAPI

#include <papi.h>

class PapiBenchmarker {
public:
	PapiBenchmarker() {

	}

	void addEvent(long event);

	void start();
	void stop();

};



#else
/*
 * If PAPI support was not active during compile time or maybe we are on an OS that doen't support PAPI
 * create a dummy papi class so that the benchmarks can still be executed with the elapsed time as a result.
 */
 
#include "TimeBenchmarker.h"

class DummyPapiBenchmarker : TimeBenchmarker {
public:
	DummyPapiBenchmarker() {

	}

	void addEvent(long event);

	void start();
	void stop();

};

typedef DummyPapiBenchmarker PapiBenchmarker;


#endif



#endif