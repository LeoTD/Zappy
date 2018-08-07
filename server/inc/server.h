
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
