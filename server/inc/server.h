
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

# define ERR_OUT(msg)		({ perror(msg); exit(-1); })
# define CMD_COUNTDOWN(plr)	(plr->cmd_list->delay_cycles)
# define CMD_READY(plr)		(CMD_COUNTDOWN(plr) == 0)
# define DO_CMD_FUNC(cmd)	(cmd->do_cmd(cmd->player_id, cmd->args))
# define NEXT_CMD(cmd)		(cmd = cmd->next)

# define LINEMATE 0
# define DERAUMERE 1
# define SIBUR 2
# define MENDIANE 3
# define PHIRAS 4
# define THYSTAME 5

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

typedef struct			s_plist
{
	t_player			*p;
	struct s_plist		*next;
}						t_plist;

typedef struct			s_game_info
{
	t_tile				**tile;
	int					x;
	int					y;
	int					teams;
	t_plist				**empty_avatars;
}						t_game_info;

typedef struct			s_cmd
{
	struct s_cmd		*next;
	int					player_id;		//Can we do this better?
	t_cmd_func			do_cmd;
	void				*args;
	int					timestamp;
	int					delay_cycles;
}						t_cmd;

typedef struct			s_cmd_queue
{
	struct s_cmd_queue	*next_plr;
	struct s_cmd		*cmd_list;
	int					player_id;
	int					cmd_count;
}						t_cmd_queue;

/*
** Global Variables:
*/

t_game_info					*g_map;

/*
** server.c
*/

int						get_server_socket(int port);
int						accept_and_poll_clients(int server);

/*
** Map Functions:
*/

int						create_map(int, int);
int						place_stone(int type, t_tile *t);
int						remove_stone(int type, t_tile *t);
int						place_random_stones(int type, int pool);

t_tile					*get_adj_tile(t_tile *home, int dir);
t_tile					*get_tile_NS(t_tile *home, int v);
t_tile					*get_tile_EW(t_tile *home, int v);

/*
** User commands:
*/

typedef int				(*t_cmd_func)(int, void *);

char					*advance(int player_id, void *arg);
char 					*turn(int player_id, void *arg);
char 					*see(int player_id, void *arg);
char 					*inventory(int player_id, void *arg);
char 					*take(int player_id, void *arg);
char 					*put(int player_id, void *arg);
char 					*kick(int player_id, void *arg);
char 					*broadcast(int player_id, void *arg);
char 					*incantation(int player_id, void *arg);
char 					*fork_player(int player_id, void *arg);
char 					*connect_nbr(int player_id, void *arg);

/*
** Scheduler commands
*/

int						schd_step_cycle(t_cmd **lit_cmds);
int						schd_add_plr(int player_id);
int						schd_kill_plr(int player_id);
int						schd_add_cmd(int player_id, t_cmd_func cmd,
										void *args, int delay_cycles);

/*
** Executioner commands
*/

int						exec_utioner(t_cmd *cmd_exec_list);
void					exec_free_cmds(t_cmd *list);

#endif
