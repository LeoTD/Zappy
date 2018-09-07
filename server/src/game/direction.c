#include "server.h"
#include "player_type.h"

#define MIN_DIRECTION NORTH
#define NUM_DIRECTIONS 8
#define DNORM(d) ((d) - MIN_DIRECTION)
#define DCLAMP(d) ((((d) + NUM_DIRECTIONS) % NUM_DIRECTIONS) + MIN_DIRECTION)

int		direction_sub(enum e_directions d1, enum e_directions d2)
{
	return (DCLAMP(DNORM(d1) - DNORM(d2)));
}

int		direction_add(enum e_directions d1, enum e_directions d2)
{
	return (DCLAMP(DNORM(d1) + DNORM(d2)));
}

int		opposite_direction(enum e_directions d)
{
	return (direction_add(d, DCLAMP(NUM_DIRECTIONS / 2)));
}

int		perceived_direction(enum e_directions d, t_player *p)
{
	return (direction_sub(d, p->facing));
}
