#include "server.h"

#define NSEC_PER_SEC 1000000000
#define NSEC_PER_TICK (NSEC_PER_SEC / g_opts.tickrate)

static struct timespec	g_timestamp;
static long				g_next_tick_nsec;

void					init_tick_timer(void)
{
	g_next_tick_nsec = NSEC_PER_TICK;
	clock_gettime(CLOCK_MONOTONIC_RAW, &g_timestamp);
}

long					timediff(struct timespec *late, struct timespec *early)
{
	return ((late->tv_sec - early->tv_sec) * NSEC_PER_SEC
			+ late->tv_nsec - early->tv_nsec);
}

int						have_we_ticked(void)
{
	struct timespec	now;
	long			diff;

	clock_gettime(CLOCK_MONOTONIC_RAW, &now);
	diff = timediff(&now, &g_timestamp);
	assert(diff >= 0);
	g_next_tick_nsec -= diff;
	memcpy(&g_timestamp, &now, sizeof(now));
	if (g_next_tick_nsec <= 0)
	{
		g_next_tick_nsec = NSEC_PER_TICK;
		return (1);
	}
	else
		return (0);
}
