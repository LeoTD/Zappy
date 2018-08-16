#ifndef GAME_INFO_TYPE_H
# define GAME_INFO_TYPE_H
# include "server.h"
# include "vec_type.h"

struct s_game_info
{
	t_tile				**tile;
	t_vec				dim;
	int					teams;
	int					*players_on_team;
	t_plist				**empty_avatars;
};
#endif
