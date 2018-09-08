#ifndef TILE_TYPE_H
# define TILE_TYPE_H
# include "server.h"

struct s_tile
{
	t_player			**players;
	int					parray_size;
	int					x;
	int					y;
	t_objcount			count;
};

#endif
