
#ifndef SERVER_H
# define SERVER_H
# include <stdio.h>
# include <stdlib.h>

typedef struct			s_tile
{
	struct s_player		*players;
	int					num_players;
	int					stones[6];
	int					food;
	int					x;
	int					y;
}						t_tile;

typedef struct			s_player
{
	struct s_tile		*tile;
	int					facing;
	int					stones[6];
	int					food;
	int					energy;
	int					level;
	int					id;
	int					team_id;
	int					egg;
}						t_player;
#endif
