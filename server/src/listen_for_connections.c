#include "server.h"

static int	g_server_fd = -1;

inline int	get_server_fd(void)
{
	return (g_server_fd);
}

void		listen_for_connections(int port)
{
	struct sockaddr_in	server;
	socklen_t			len;
	int					fd;
	int					optval;

	if ((fd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)) < 0)
		ERR_OUT("socket");
	printf("server starting with fd %d\n", fd);
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
	g_server_fd = fd;
	socket_lookup_add(fd, SERVER);
}

void		handle_waiting_connection_data(int fd)
{
	if (fd == get_server_fd())
		initiate_user_connection_handshake(fd);
	else if (socket_lookup_has(fd, HANDSHAKE))
		complete_user_connection_handshake(fd);
	else
	{
		assert(socket_lookup_has(fd, ACTIVE_PLAYER));
		receive_user_message(fd);
	}
}
