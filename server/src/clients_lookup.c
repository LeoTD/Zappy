#include "server.h"
#include "client_type.h"

static t_client		*g_clients[MAX_CLIENTS + 1] = { 0 };
static int			g_capacity = MAX_CLIENTS;
static int			g_count = 0;

inline t_client		**get_clients(void)
{
	return (g_clients);
}

void				register_client(int sock_fd, int id, int type)
{
	if (g_count == g_capacity)
		FATAL("rewrite clients_lookup.c before making that many clients.");
	g_clients[g_count] = new_client(sock_fd, id, type);
	++g_count;
	socket_lookup_remove(sock_fd);
	socket_lookup_add(sock_fd, type);
	return ;
}

void				initialize_clients(void)
{
	bzero(g_clients, sizeof(g_clients));
	g_count = 0;
}

t_client			*get_client_by_id(int id)
{
	int		i;

	i = 0;
	while (i < g_count)
	{
		assert(g_clients[i]);
		if (g_clients[i]->id == id)
			return (g_clients[i]);
		++i;
	}
	return (NULL);
}

t_client			*get_client_by_socket_fd(int sock_fd)
{
	int		i;

	i = 0;
	while (i < g_count)
	{
		assert(g_clients[i]);
		if (g_clients[i]->socket_fd == sock_fd)
			return (g_clients[i]);
		++i;
	}
	return (NULL);
}

void				unregister_client_by_id(int id)
{
	int			i;
	t_client	*c;
	t_client	*last_in_array;

	i = 0;
	while (i < g_count)
	{
		assert(g_clients[i]);
		if (g_clients[i]->id == id)
		{
			c = g_clients[i];
			socket_lookup_remove(c->socket_fd);
			close(c->socket_fd);
			last_in_array = g_clients[g_count - 1];
			g_clients[i] = last_in_array;
			g_clients[g_count - 1] = NULL;
			free(c);
			--g_count;
			return ;
		}
		++i;
	}
}
