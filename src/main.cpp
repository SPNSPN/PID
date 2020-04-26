#include <stdio.h>
#include <unistd.h>
#include <math.h> // sqrt()
#include "PID.h"

int main(int argc, char **argv)
{
			// p_gain, i_gain, d_gain, pre_d_gain
	PID pid(1.0, 0.0, 0.05, 0.0
			// lower_limit, upper_limit, offset
			, 1.0, -1.0, 0.0
			// cutoff_hz, sampling_hz, lpf_q
			, 20.0, 200.0, 1.0 / sqrt(2.0));

	// sample plant
	const double m = 1.0, c = 0.0, k = 0.0;
	double acc = 0.0, vel = 0.0, pos = 0.0;

	for(size_t i = 0; i < 500; ++i)
	{
		// sample input
		double target = i > 100 ? 100.0 : 0.0;

		clock_t sim_clock = i * 0.002 * CLOCKS_PER_SEC;
		pid.push_err(target, pos, sim_clock);
		double f = pid.pop_ctrl();

		acc = f / m - c * vel - k * pos;
		vel += acc;
		pos += vel;

		printf("%f,%f,%f\n", (double)(sim_clock) / (double)(CLOCKS_PER_SEC), target, pos);
	}

	return 0;
}

