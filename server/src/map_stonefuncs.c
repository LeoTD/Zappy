
#include "server.h"

int			place_stone(int type, int amount, t_tile *t)
{
	if (!t)
		return (-1);
	t->stones[type] += amount;
	return (0);
}

/*
** Returns 0 on success.
** If requesting more stones than are present, returns -1.
*/

int			remove_stone(int type, int amount, t_tile *t)
{
	if (!t || t->stones[type] < amount)
		return (-1);
	t->stones[type] -= amount;
	return (0);
}
