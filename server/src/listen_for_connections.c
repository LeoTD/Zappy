#include "server.h"

void	listen_for_connections(int port)
{
	struct sockaddr_in	server;
	socklen_t			len;
	int					fd;
	int					optval;

	if ((fd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)) < 0)
		ERR_OUT("socket");
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
	set_connection_type(fd, SERVER);
}

void	handle_waiting_connection_data(int fd)
{
	if (is_connection_type(fd, SERVER))
		initiate_user_connection_handshake(fd);
	else if (is_connection_type(fd, HANDSHAKE))
		complete_user_connection_handshake(fd);
	else
	{
		assert(is_connection_type(fd, USER));
		receive_user_message(fd);
	}
}
