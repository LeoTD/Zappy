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
# include <sys/time.h>
# include <unistd.h>


# define MAX_COMMANDS		10
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

# define MAX_CLIENTS (FD_SETSIZE - 4)

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
# define MAX_BROADCAST_LENGTH 4096
# define MAX_USER_COMMAND_LENGTH MAX_BROADCAST_LENGTH
# define MAX_OBJ_NAME_LENGTH 9 // deraumere

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

enum			e_socktype
{
	HANDSHAKE,
	SERVER,
	ACTIVE_PLAYER,
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
	int					players;
	int					*players_on_team;
	t_plist				**empty_avatars;
	int					pids;
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
	int					teamcount;
}						g_opts;

/*
** player_data_api.c
*/

void					player_list_init(void);
t_player				*get_player(int pid);
int						get_player_list_size(void);

// player_data_api_2.c
int             		delete_player_from_list(t_player *p);

/*
** player_actions.c:
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
int						player_pickup_stone(int type, t_tile *t, t_player *player);

t_tile					*get_random_tile(void);
int						place_random_stones(int type, int pool);
int						place_random_food(int pool);
int						player_place_food(t_tile *tile, t_player *player);
int						pickup_food(t_tile *t, t_player *player);
int						move_player(t_player *p, int dir);

//	game/game_init.c
int						game_init(int x, int y, int teams, int players);

//	game/game_upkeep.c
void					game_upkeep(void);

//	game/player_creation.c
int						assign_avatar(int team_id);
t_player				*new_player(int team_id, int team_pid);
t_player				*new_player_on_tile(int team_id, int x, int y);

//	game/player_death.c
int						kill_active_player(int pid);
int						kill_inactive_player(t_player *p);
int 			        *get_dead_players(int *size);
void        			reset_obituary(void);

//	game/player_empty_list_funcs.c
int						get_team_open_slots(int team);
int						get_team_open_slots_by_pid(int pid);

//	find_resouces.c
char					*find_food(t_player *player);
char					*find_stones(t_player *player);

t_tile					*get_adj_tile(t_tile *home, int dir);
t_tile					*get_tile_NS(t_tile *home, int v);
t_tile					*get_tile_EW(t_tile *home, int v);

int						remove_player_from_tile(t_player *p, t_tile *t);
int						add_player_to_tile(t_player *p, t_tile *t);
t_player				*is_player_on_tile(t_player *p, t_tile *t);

int						get_new_player_id(void);
void					cleanup_player_list(void);
t_player				*get_player(int pid);
int						add_player_to_list(t_player *t);
int						grow_list(void);
int						add_player_to_team_waitlist(t_player *p);
t_player				*remove_player_from_waitlist(int team);

/*
**	get_player_inventory.c
*/

char					*wrap(char *str);
char					*delimit(char *str1, char *d, char *str2);
char					*search_inventory(t_player *player);
char					*get_player_inventory(int pid);

/*
**	game/kick.c
*/

int						attempt_to_kick(int pid);

// ?

int						*remove_pid(int *parray, int size, int current);

// game/vision.c
char					*see_tiles(int pid);
// game/existing_counts.c
char					*existing_food_count(t_tile *tile);
char					*existing_player_count(t_tile *tile);
char					*existing_stone_count(t_tile *tile);

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

/*
**	User game helpers:
*/

char					*get_player_inventory(int pid);


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
void					socket_lookup_init(int do_close);
void					socket_lookup_add(int fd, enum e_socktype type);
void					socket_lookup_remove(int sock_fd);
int						socket_lookup_has(int sock_fd, enum e_socktype type);
int						iter_next_readable_socket(void);
	
// listen_for_connections.c
void					listen_for_connections(int port);
void					handle_waiting_connection_data(int fd);
int						get_server_fd(void);

// cmdfunc_type.c
int						get_cmdfunc_tick_delay(t_cmdfunc f);
t_cmdfunc				string_to_cmdfunc(char *string, char **arg_ptr);

// command_type.c
t_command				*new_cmd(t_cmdfunc);
void					free_cmd(t_command *cmd);
t_command				*string_to_command(char *string);

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
void					initialize_user_clients(void);
t_client				**get_clients(void);
void					register_user_client(int sock_fd, int player_id);
t_client				*get_client_by_player_id(int player_fd);
t_client				*get_client_by_socket_fd(int sock_fd);
void					unregister_client_by_player_id(int player_id);

// send_stringified_responses.c
void					send_stringified_responses(t_command_list *lst);

// time_to_tick.c
void					init_tick_timer(void);
int						have_we_ticked(void);

/*
**	str_utils.c:
*/

char					*strnew(char *str);
char					*strjoin_free(char *str1, char *str2);
char					*itoa(int n);

int						*get_current_tile_player_count(int pid, int *count);

#endif
