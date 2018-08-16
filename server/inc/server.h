#ifndef SERVER_H
# define SERVER_H
# include <arpa/inet.h>
# include <assert.h>
# include <limits.h>
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

# define DEFAULT_PARRAY 8

# define DEFAULT_FOOD 0
# define DEFAULT_ENERGY 1260
# define DEFAULT_LEVEL 1
# define EGG_TIMER 300
# define ENERGY_PER_FOOD 126
# define FATAL(msg) ({ fprintf(stderr, "%s: %s\n", __func__, msg); exit(-1); })
# define HEREMSG fprintf(stderr, "MADE IT %s:%d\n", __func__, __LINE__)

// for command_line_options.c and receive_user_message.c
# define MAX_TEAM_NAME_LENGTH 63

typedef char					*(*t_cmdfunc)(int player_id, void *args);
typedef struct s_command		t_command;
typedef struct s_command_list	t_command_list;
typedef struct s_command_queue	t_command_queue;
typedef struct s_client			t_client;
typedef struct s_vec
{
	int x;
	int y;
}								t_vec;
typedef struct s_tile			t_tile;
typedef struct s_player			t_player;

enum			e_connection_type
{
	HANDSHAKE,
	USER,
	SERVER,
	GFX
};

enum			e_directions
{
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST
};

typedef struct			s_plist
{
	t_player			*p;
	struct s_plist		*next;
}						t_plist;

typedef struct			s_game_info
{
	t_tile				**tile;
	t_vec				dim;
	int					teams;
	int					*players_on_team;
	t_plist				**empty_avatars;
}						t_game_info;

t_game_info				*g_map;
extern struct			s_opts
{
	int					tickrate;
	int					server_port;
	int					world_width;
	int					world_height;
	int					initial_players_per_team;
	char				**team_names;
}						g_opts;

/*
** Player api:
*/

t_player				*get_player(int pid);

/*
**	player_actions.c:
*/

void					turn_left(int pid);
void					turn_right(int pid);
void					walk_forward(int pid);

int						attempt_to_take(int pid, char *obj);
int						attempt_to_put(int pid, char *obj);

/*
** Game Engine Functions:
*/

int						create_map(int, int);
int						place_stone(int type, t_tile *t);
int						player_place_stone(int type, t_tile *t, t_player *player);
int						remove_stone(int type, t_tile *t);
int						pickup_stone(int type, t_tile *t, t_player *player);

t_tile					*get_random_tile(void);
int						place_random_stones(int type, int pool);
int						place_random_food(int pool);
int						player_place_food(t_tile *tile, t_player *player);
int						pickup_food(t_tile *t, t_player *player);
int						move_player(t_player *p, int dir);

t_tile					*get_adj_tile(t_tile *home, int dir);
t_tile					*get_tile_NS(t_tile *home, int v);
t_tile					*get_tile_EW(t_tile *home, int v);

int						remove_player_from_tile(t_player *p, t_tile *t);
int						add_player_to_tile(t_player *p, t_tile *t);
t_player				*is_player_on_tile(t_player *p, t_tile *t);

t_player				*new_player(int egg, int team_id, int team_pid);
int						get_new_player_id(void);
void					cleanup_player_list(void);
t_player				*get_player(int pid);
int						add_player_to_list(t_player *t);
int						grow_list(void);
int						add_player_to_team_waitlist(t_player *p);
t_player				*remove_player_from_waitlist(int team);

/*
** User commands:
*/

char					*advance(int player_id, void *arg);
char 					*turn(int player_id, void *arg);
char					*left(int player_id, void *args);
char					*right(int player_id, void *args);
char 					*see(int player_id, void *arg);
char 					*inventory(int player_id, void *arg);
char 					*take(int player_id, void *arg);
char 					*put(int player_id, void *arg);
char 					*kick(int player_id, void *arg);
char 					*broadcast(int player_id, void *arg);
char 					*incantation(int player_id, void *arg);
char 					*fork_player(int player_id, void *arg);
char 					*connect_nbr(int player_id, void *arg);

// command_line_options.c
void					parse_command_line_options(int argc, char **argv);

// time_to_tick.c
int						have_we_ticked(void);

// remove_dead_players.c
void					remove_dead_players(void);

// dequeue_commands.c
t_command_list 			*dequeue_commands(t_client **clients);

// execute_command_list.c
void					execute_command_list(t_command_list *lst);

// game_over.c
int						is_game_over(int *winning_team_id_ptr);
void					handle_game_over(int winning_team_id);

// send_stringified_responses.c
void					send_results_to_users(t_command_list *lst);

// decrement_user_command_timers.c
void					decrement_user_command_timers(t_client **clients);

//active_socket_info.c
void					set_connection_type(int fd, enum e_connection_type type);
int						get_socket_with_available_data(void);
void					forget_connection(int sock_fd);
int						is_connection_type(int sock_fd, enum e_connection_type type);
void					unset_connection_type(int sock_fd, enum e_connection_type type);
	
// listen_for_connections.c
void					listen_for_connections(int port);
void					handle_waiting_connection_data(int fd);

// cmdfunc_type.c
int						get_cmdfunc_tick_delay(t_cmdfunc f);

// command_type.c
t_command				*new_cmd(t_cmdfunc, int player_id);
void					free_cmd(t_command *cmd);

// client_type.c
t_client				*new_client(int socket_fd, int player_id);
void					free_client(t_client *client);

// command_list_type.c
t_command_list			*new_cmdlist(t_command *cmd);
void					free_cmdlist(t_command_list *list);

// command_queue_type.c
t_command_queue			*new_cmdqueue(void);
void					free_cmdqueue(t_command_queue *q);
int						enqueue_command(t_command_queue *q, t_command *cmd);
t_command_list			*dequeue_command(t_command_queue *q);

// handshake.c
void					initiate_user_connection_handshake(int server_fd);
void					complete_user_connection_handshake(int cli_fd);

// receive_user_message.c
void					receive_user_message(int cli_fd);

// user_clients_lookup.c
t_client				**get_clients(void);
void					register_user_client(int sock_fd, int player_id);
t_client				*get_client_by_player_id(int player_fd);
t_client				*get_client_by_socket_fd(int sock_fd);
void					unregister_user_client(t_client *client);

// send_stringified_responses.c
void					send_stringified_responses(t_command_list *lst);

// time_to_tick.c
int						have_we_ticked(void);

#endif
