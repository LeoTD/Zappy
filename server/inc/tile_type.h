#ifndef TILE_TYPE_H
# define TILE_TYPE_H
# include "server.h"

struct s_tile
{
	t_player			**players;
	int					parray_size;
	int					num_players;
	int					stones[6];
	int					food;
	int					x;
	int					y;
};
#endif
