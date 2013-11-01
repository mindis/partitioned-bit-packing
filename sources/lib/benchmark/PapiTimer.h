#ifndef PAPI_TIMER_H_
#define PAPI_TIMER_H_



#ifdef WITH_PAPI

#include <papi.h>
#include <pthread.h>

class PAPITimer {
public:
	PAPITimer() {
		_event_set = PAPI_NULL;
		initializePAPI();
	}

	~PAPITimer() {
		delete[] _values;
	}

	bool addCounter(long event) {
		if (PAPI_add_event(_event_set, event) != PAPI_OK) {
			printf("Counter could not be added!\n");
			return false;
		}
		_events.push_back(event);
		return true;
	}

	bool start() {
		if (_events.size() > 0 && PAPI_start(_event_set) != PAPI_OK) {
			printf("Could not start PAPI\n");
			return false;
		}
		_us = PAPI_get_real_usec();
		return true;
	}

	bool stop() {
		if (_events.size() > 0) {
			_values = new long_long[_events.size()];
			if (PAPI_stop(_event_set, _values) != PAPI_OK) {
				printf("Could not stop PAPI\n");
				return false;
			}
		}
		_us = PAPI_get_real_usec() - _us;
		return true;
	}

	long_long getValue(uint index) {
		return _values[index];
	}

private:
	std::vector<int> _events;
	int _event_set;
	long_long _us;
	long_long *_values;


	bool initializePAPI() {
		if (!this->initializePAPILibrary())
			return false;
		if (PAPI_thread_init(pthread_self) != PAPI_OK) {
			printf("Error Initializing PAPI-Thread\n");
			return false;
		}
		if (PAPI_create_eventset(&_event_set) != PAPI_OK) {
			printf("Error creating the event set\n");
			return false;
		}
		return true;
	}

	static bool initializePAPILibrary() {
		if (PAPI_is_initialized() == PAPI_NOT_INITED) {
			if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
				printf("PAPI library init error!\n");
				return false;
			}
		}
		return true;
	}
};


class PAPIClockCycleTimer {
public:
	PAPIClockCycleTimer() {
		_papi_timer.addCounter(PAPI_TOT_CYC);
	}

	PAPIClockCycleTimer(bool do_start) {
		_papi_timer.addCounter(PAPI_TOT_CYC);
		if (do_start) start();
	}

	void start() {
		_papi_timer.start();
	}

	long stop() {
		_papi_timer.stop();
		_result = _papi_timer.getValue(0);
		return _result;
	}

	unsigned long result() {
		return _result;
	}

private:
	PAPITimer _papi_timer;
	unsigned long _result;
};


#else
/*
 * If PAPI support was not active during compile time or maybe we are on an OS that doen't support PAPI
 * create a dummy papi class so that the benchmarks can still be executed with the elapsed time as a result.
 */
 
#include "Timer.h"

typedef Timer PAPIClockCycleTimer;

#endif



#endif