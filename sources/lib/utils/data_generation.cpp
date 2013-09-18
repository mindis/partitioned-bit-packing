#include "data_generation.h"


namespace utils {
	static unsigned int g_seed = 15145;

	void fast_srand(int seed) {
		g_seed = seed;
	}

	unsigned int fastrand() {
		g_seed = (214013 * g_seed + 2531011);
		//printf("FR: %u\n", g_seed);
		return g_seed;//(g_seed >> 16) & 0x7FFF;
	}
}