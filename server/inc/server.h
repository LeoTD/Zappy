
#ifndef SERVER_H
# define SERVER_H
# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

enum					e_directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NORTHEAST,
	NORTHWEST,
	SOUTHEAST,
	SOUTHWEST
};

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

typedef struct			s_map_info
{
	t_tile				**tile;
	int					x;
	int					y;
}						t_map_info;

/*
** Global Variables:
*/

t_map_info					*g_map;

/*
** Map Functions:
*/

int						remove_stone(int type, int amount, t_tile *t);
int						place_stone(int type, int amount, t_tile *t);
int						place_random_stones(int type, int pool);
int						create_map(int, int);

/*
** User commands:
*/

typedef int				(*t_command)(int, void *);

int						advance(int player_id, void *arg);
int						turn(int player_id, void *arg);
int						see(int player_id, void *arg);
int						inventory(int player_id, void *arg);
int						take(int player_id, void *arg);
int						put(int player_id, void *arg);
int						kick(int player_id, void *arg);
int						broadcast(int player_id, void *arg);
int						incantation(int player_id, void *arg);
int						fork_player(int player_id, void *arg);
int						connect_nbr(int player_id, void *arg);
#endif
