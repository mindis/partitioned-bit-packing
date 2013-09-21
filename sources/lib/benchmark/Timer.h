#ifndef TIMER_H_
#define TIMER_H_


#include <sys/time.h>

class Timer {
public:
	static long run_ms(void (*fn)()) {
		Timer timer = Timer(fn);
		return timer.milliseconds();
	}

	Timer() : m_hasFinished(false) {}
	Timer(bool doStart) : m_hasFinished(false) {
		if (doStart) start();
	}

	Timer(void (*fn)()) : m_hasFinished(false) {
		start();
		fn();
		stop();
	}


	/*
	 * @brief starts the time counter
	 */
	void start() {
		gettimeofday(&m_start, NULL);
	}

	/*
	 * @brief stops the time counter and returns passed microseconds
	 */
	long stop() {
		gettimeofday(&m_end, NULL);
		m_microseconds = (m_end.tv_sec - m_start.tv_sec) * 1000000 + (m_end.tv_usec - m_start.tv_usec);
		return microseconds();
	}

	long microseconds() { return m_microseconds; }
	long milliseconds() { return m_microseconds / 1000; }
	long seconds() { return m_microseconds / 1000000; }

protected:
	bool m_hasFinished;
	long m_microseconds;
	timeval m_start, m_end;
};

#endif