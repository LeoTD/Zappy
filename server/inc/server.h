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

# define FATAL(msg) ({ fprintf(stderr, "%s: %s\n", __func__, msg); exit(-1); })
# define ERR_OUT(msg) ({ perror(msg); exit(-1); })
# define HEREMSG fprintf(stderr, "MADE IT %s:%d\n", __func__, __LINE__)

// for command_line_options.c and receive_user_message.c
# define MAX_TEAM_NAME_LENGTH 63

enum			e_connection_type
{
	HANDSHAKE,
	USER,
	SERVER,
	GFX
};

typedef void					(*t_cmdfunc)(int player_id, void *args);
typedef struct s_command		t_command;
typedef struct s_command_list	t_command_list;
typedef struct s_command_queue	t_command_queue;
typedef struct s_client			t_client;
typedef struct s_vec			t_vec;

extern struct	s_opts
{
	int		tickrate;
	int		server_port;
	int		world_width;
	int		world_height;
	int		initial_players_per_team;
	char	**team_names;
}				g_opts;

//active_socket_info.c
void	set_connection_type(int fd, enum e_connection_type type);
int		get_socket_with_available_data(void);
void	forget_connection(int sock_fd);
int		is_connection_type(int sock_fd, enum e_connection_type type);
void	unset_connection_type(int sock_fd, enum e_connection_type type);

// listen_for_connections.c
void							listen_for_connections(int port);
void							handle_waiting_connection_data(int fd);

// cmdfunc_type.c
int								get_cmdfunc_tick_delay(void (*f)(int, void *));

// command_type.c
t_command						*new_cmd(t_cmdfunc, int player_id);
void							free_cmd(t_command *cmd);

// client_type.c
t_client						*new_client(int socket_fd, int player_id);
void							free_client(struct s_client *client);

// command_list_type.c
t_command_list					*new_cmdlist(t_command *cmd);
void							free_cmdlist(t_command_list *list);

// command_queue_type.c
t_command_queue					*new_cmdqueue(void);
void							free_cmdqueue(t_command_queue *q);
int								enqueue_command(t_command_queue *q, t_command *cmd);
t_command_list					*dequeue_command(t_command_queue *q);

// handshake.c
void		initiate_user_connection_handshake(int server_fd);
void		complete_user_connection_handshake(int cli_fd);

// receive_user_message.c
void		receive_user_message(int cli_fd);

// user_clients_lookup.c
t_client			**get_clients(void);
void				register_user_client(int sock_fd, int player_id);
t_client			*get_client_by_player_id(int player_fd);
t_client			*get_client_by_socket_fd(int sock_fd);
void				unregister_user_client(t_client *client);

// user_commands/*.c
t_cmdfunc						advance;
t_cmdfunc						right;
t_cmdfunc						left;
t_cmdfunc						see;
t_cmdfunc						inventory;
t_cmdfunc						take;
t_cmdfunc						put;
t_cmdfunc						kick;
t_cmdfunc						broadcast;
t_cmdfunc						incantation;
t_cmdfunc						fork_player;
t_cmdfunc						connect_nbr;

#endif
