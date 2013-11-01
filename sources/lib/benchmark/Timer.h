#ifndef TIMER_H_
#define TIMER_H_


#include <sys/time.h>

class Timer {
public:
	static long run_ms(void (*fn)()) {
		Timer timer = Timer(fn);
		return timer.milliseconds();
	}

	Timer() {}

	Timer(bool do_start) {
		if (do_start) start();
	}


	/*
	 * @brief starts the time counter
	 */
	void start() {
		gettimeofday(&_start, NULL);
	}

	/*
	 * @brief stops the time counter and returns passed microseconds
	 */
	long stop() {
		gettimeofday(&_end, NULL);
		_microseconds = (_end.tv_sec - _start.tv_sec) * 1000000 + (_end.tv_usec - _start.tv_usec);
		return microseconds();
	}

	unsigned long result() {
		return _microseconds;
	}

	long microseconds() { return _microseconds; }
	long milliseconds() { return _microseconds / 1000; }
	long seconds() { return _microseconds / 1000000; }

protected:
	bool _has_finished;
	long _microseconds;
	timeval _start, _end;
};

#endif