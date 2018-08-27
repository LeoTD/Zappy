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

char	*existing_food_count(t_tile *tile);
char	*existing_player_count(t_tile *tile, int pid);
char	*add_existing_stone(t_tile *tile, int n);

#endif
