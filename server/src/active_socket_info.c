#include "server.h"

static fd_set	g_handshake_fds = { 0 };
static fd_set	g_user_fds = { 0 };
static fd_set	g_all_fds = { 0 };
static int		g_max_fd = 0;
static int		g_server_fd = -1;

void	set_connection_type(int sock_fd, enum e_connection_type type)
{
	FD_SET(sock_fd, &g_all_fds);
	if (sock_fd > g_max_fd)
		g_max_fd = sock_fd;
	if (type == SERVER)
		g_server_fd = sock_fd;
	else if (type == USER)
		FD_SET(sock_fd, &g_user_fds);
	else if (type == HANDSHAKE)
		FD_SET(sock_fd, &g_handshake_fds);
	else
		FATAL("bad connection type");
}

void	unset_connection_type(int sock_fd, enum e_connection_type type)
{
	if (type == USER)
		FD_CLR(sock_fd, &g_user_fds);
	else if (type == HANDSHAKE)
		FD_CLR(sock_fd, &g_handshake_fds);
	else
		FATAL("bad connection type");
}

int		is_connection_type(int sock_fd, enum e_connection_type type)
{
	if (type == SERVER)
		return (sock_fd == g_server_fd);
	if (type == USER)
		return (FD_ISSET(sock_fd, &g_user_fds));
	if (type == HANDSHAKE)
		return (FD_ISSET(sock_fd, &g_handshake_fds));
	else
		FATAL("bad connection type");
}

void	forget_connection(int sock_fd)
{
	int		new_max_fd;

	if (g_max_fd == sock_fd)
	{
		new_max_fd = g_max_fd - 1;
		while (!(FD_ISSET(new_max_fd, &g_all_fds)))
		{
			--new_max_fd;
			assert(new_max_fd > 0);
		}
		g_max_fd = new_max_fd;
	}
	unset_connection_type(sock_fd, &g_user_fds);
	unset_connection_type(sock_fd, &g_handshake_fds);
	unset_connection_type(sock_fd, &g_all_fds);
	close(sock_fd);
}

int		get_readable_socket(void)
{
	static int		prev = -1;
	static fd_set	readable;
	int				curr;

	if (prev == g_max_fd)
		return ((prev = -1));
	else if (prev == -1)
	{
		readable = g_all_fds;
		if (select(g_max_fd + 1, &readable, NULL, NULL, NULL) == -1)
			ERR_OUT("select");
	}
	curr = prev + 1;
	while (curr <= g_max_fd)
	{
		if (FD_ISSET(curr, &readable))
			return ((prev = curr))
		++curr;
	}
	prev = g_max_fd;
	return (-1);
}
