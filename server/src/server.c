#include "server.h"
#include "test.h" // remove me

static fd_set		g_all_fds;
static int			g_max_fd;

int		get_server_socket(int port)
{
	struct sockaddr_in	server;
	socklen_t			len;
	int					fd;
	int					optval;

	if ((fd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)) < 0)
		ERR_OUT("socket");
	g_max_fd = fd;
	FD_SET(fd, &g_all_fds);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);
	if (bind(fd, (struct sockaddr *)&server, sizeof(server)) == -1)
		ERR_OUT("bind");
	len = sizeof(server);
	if (getsockname(fd, (struct sockaddr *)&server, &len) == -1)
		ERR_OUT("getsockname");
	optval = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1)
		ERR_OUT("setsockopt");
	if (listen(fd, 3) == -1)
		ERR_OUT("listen");
	return (fd);
}

int		handle_client_connection_attempt(int serv_fd)
{
	int					cli_fd;
	struct sockaddr_in	client;
	socklen_t			len;

	len = sizeof(struct sockaddr);
	if ((cli_fd = accept(serv_fd, (struct sockaddr *)&client, &len)) == -1)
		ERR_OUT("accept");
	if (cli_fd > g_max_fd)
		g_max_fd = cli_fd;
	FD_SET(cli_fd, &g_all_fds);
	return (0);
}

ssize_t	handle_client_message(int cli_fd)
{
	ssize_t				count;
	char				buf[256];
	struct sockaddr_in	client;
	socklen_t			len;

	count = recv(cli_fd, buf, sizeof(buf) - 1, 0);
	len = sizeof(client);
	getsockname(cli_fd, (struct sockaddr *)&client, &len);
	if (count > 0)
	{
		buf[count] = '\0';
#ifdef TESTING
		g_make_server_die = !strncmp("kill", buf, 4);
#endif
	}
	else
	{
		if (count == -1)
			perror("recv");
		close(cli_fd);
		FD_CLR(cli_fd, &g_all_fds);
	}
	return (0);
}

int		accept_and_poll_clients(int serv_fd)
{
	fd_set				readable;
	int					curr_fd;

	readable = g_all_fds;
	if (select(g_max_fd + 1, &readable, NULL, NULL, NULL) == -1)
		ERR_OUT("select");
	curr_fd = 0;
	while (curr_fd <= g_max_fd)
	{
		if (FD_ISSET(curr_fd, &readable))
		{
			if (curr_fd == serv_fd)
				handle_client_connection_attempt(curr_fd);
			else
				handle_client_message(curr_fd);
		}
		curr_fd++;
	}
	return (0);
}
