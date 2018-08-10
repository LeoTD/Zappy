#include "server.h"

/* Optionally print the results of movements */
//#define PRINTF_MOVES

static void		go(int dir, t_tile **t_ptr)
{
	*t_ptr = get_adj_tile(*t_ptr, dir);
//	printf("Moved: %d -- Curr tile: (%d, %d)\n", dir, (*t_ptr)->x, (*t_ptr)->y);
}

int			test_map_movement(void)
{
	t_tile		*t;

	g_map = NULL;
	create_map(17, 7);
	t = &g_map->tile[0][0];
#ifdef PRINTF_MOVES
	printf("Home tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 137; i++)
		go(NORTH, &t);
#ifdef PRINTF_MOVES
	printf("Moved: NORTH -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 93; i++)
		go(WEST, &t);
#ifdef PRINTF_MOVES
	printf("Moved: WEST -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 57; i++)
		go(SOUTH, &t);
#ifdef PRINTF_MOVES
	printf("Moved: SOUTH -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 127; i++)
		go(EAST, &t);
#ifdef PRINTF_MOVES
	printf("Moved: EAST -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 293; i++)
		go(SOUTHEAST, &t);
#ifdef PRINTF_MOVES
	printf("Moved: SOUTHEAST -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 73; i++)
		go(NORTHEAST, &t);
#ifdef PRINTF_MOVES
	printf("Moved: NORTHEAST -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 999; i++)
		go(SOUTHWEST, &t);
#ifdef PRINTF_MOVES
	printf("Moved: SOUTHWEST -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	for(int i = 0; i < 420; i++)
		go(NORTHWEST, &t);
#ifdef PRINTF_MOVES
	printf("Moved: NORTHWEST -- Curr tile: (%d, %d)\n", t->x, t->y);
#endif
	assert(t->x == 1 && t->y == 5);
	return (0);
}
