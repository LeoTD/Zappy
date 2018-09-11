#ifndef PLAYER_TYPE_H
# define PLAYER_TYPE_H
# include "server.h"
struct s_player
{
	t_tile				*tile;
	int					facing;
	int					energy;
	int					level;
	int					id;
	int					team_id;
	t_objcount			count;
};

#endif
