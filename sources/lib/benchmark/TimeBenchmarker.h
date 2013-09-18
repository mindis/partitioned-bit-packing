#ifndef TIME_BENCHMARKER_H_
#define TIME_BENCHMARKER_H_


class TimeBenchmarker {
public:

	TimeBenchmarker() : startMicroseconds(0), endMicroseconds(0), hasFinished(false) {

	}


	/*
	 * @brief starts the time counter
	 */
	void start();

	/*
	 * @brief stops the time counter and returns passed microseconds
	 */
	long stop();

	long microseconds();
	long milliseconds();
	long seconds();

private:
	bool hasFinished;
	long startMicroseconds, endMicroseconds;
};

#endif