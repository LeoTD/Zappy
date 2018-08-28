#ifndef PLAYER_TYPE_H
# define PLAYER_TYPE_H
# include "server.h"
struct s_player
{
	t_tile				*tile;
	int					facing;
	int					stones[6];
	int					food;
	int					energy;
	int					level;
	int					id;
	int					team_id;
};

int		player_right(t_player *player);
int		player_forward(t_player *player);
int		player_northwest(t_player *player);

#endif
