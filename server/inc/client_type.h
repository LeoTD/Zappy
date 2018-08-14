#ifndef CLIENT_TYPE_H
# define CLIENT_TYPE_H
# include "server.h"

t_client		*new_client(int socket_fd, int player_id);
void			free_client(t_client *client);

#endif
