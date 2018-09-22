#include "server.h"
#include "client_type.h"

t_client	*new_client(int socket_fd, int id, int type)
{
	t_client		*c;
	t_command_queue	*q;

	q = NULL;
	if (type == ACTIVE_PLAYER && !(q = new_cmdqueue()))
		return (NULL);
	if (!(c = malloc(sizeof(*c))))
		return (NULL);
	c->cmdqueue = q;
	c->socket_fd = socket_fd;
	c->type = type;
	c->id = id;
	return (c);
}

void		free_client(t_client *client)
{
	free_cmdqueue(client->cmdqueue);
	free(client);
}
