
#ifndef SERVER_H
# define SERVER_H
# include <arpa/inet.h>
# include <assert.h>
# include <netdb.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <unistd.h>

# define ERR_OUT(msg) ({ perror(msg); exit(-1); })
# define CMD_COUNTDOWN(plr) (plr->cmd_list->delay_cycles)

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

typedef struct			s_cmd
{
	struct s_cmd		*next;
	int					player_id;		//Can we do this better?
	t_command			cmd;
	void				*args;
	int					timestamp;
	int					delay_cycles;
}						t_cmd;

typedef struct			s_plr_cmds
{
	struct s_plr_cmds	*next_plr;
	struct s_cmd		*cmd_list;
	int					player_id;
	int					cmd_count;
}						t_plr_cmds;

/*
** Global Variables:
*/

t_map_info					*g_map;

/*
** server.c
*/

int						get_server_socket(int port);
int						accept_and_poll_clients(int server);

/*
** Map Functions:
*/

int						create_map(int, int);
int						place_stone(int type, int amount, t_tile *t);
int						remove_stone(int type, int amount, t_tile *t);
int						place_random_stones(int type, int pool);

t_tile					*get_adj_tile(t_tile *home, int dir);
t_tile					*get_tile_NS(t_tile *home, int v);
t_tile					*get_tile_EW(t_tile *home, int v);

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
