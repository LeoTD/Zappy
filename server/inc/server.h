
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
# define MAX_BROADCAST_LENGTH 4096

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

# define DEFAULT_PARRAY 8

typedef struct			s_tile
{
	struct s_player		**players;
	int					parray_size;
	int					num_players;
	int					stones[6];
	int					food;
	int					x;
	int					y;
}						t_tile;

# define DEFAULT_FOOD 0
# define DEFAULT_ENERGY 1260
# define DEFAULT_LEVEL 1
# define EGG_TIMER 300
# define ENERGY_PER_FOOD 126

typedef struct			s_player
{
	struct s_tile		*tile;
	int					facing;
	int					stones[6];
	int					food;
	int					energy;
	int					level;
	int					id;
	int					team_pid;
	int					team;
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
** server.c
*/

int						get_server_socket(int port);
int						accept_and_poll_clients(int server);

/*
** Map Functions:
*/

int						create_map(int, int);
int						place_stone(int type, int amount, t_tile *t);
int						pickup_stone(int type, int amount, t_tile *t);
int						place_food(int amount, t_tile *t);
int						pickup_food(int amount, t_tile *t);
int						place_random_stones(int type, int pool);
int						place_random_food(int pool);

t_tile					*get_adj_tile(t_tile *home, int dir);
t_tile					*get_tile_NS(t_tile *home, int v);
t_tile					*get_tile_EW(t_tile *home, int v);

/*
** Player Functions:
*/

t_player				*new_player(int egg, int team_id);
int						get_new_player_id(void);
void					cleanup_player_list(void);
t_player				*get_player(int pid);
int						add_player_to_list(t_player *t);
int						grow_list(void);

int						move_player(t_player *p, int dir);
int						add_player_to_tile(t_player *p, t_tile *t);
int						remove_player_from_tile(t_player *p, t_tile *t);
t_player				*is_player_on_tile(t_player *p, t_tile *t);

int						add_player_to_empty_list(t_player *p, int team);

/*
** User commands:
*/

typedef int				(*t_cmdfunc)(int, void *);

int						advance(int player_id, void *arg);
int						left(int player_id, void *arg);
int						right(int player_id, void *arg);
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
