#include "server.h"
#include "test.h"

void test_server_listen(void)
{
	socket_lookup_init(1);
	g_opts.server_port = 0x0;
	listen_for_connections(g_opts.server_port);
}

int	get_port_from_fd(int fd)
{
	struct sockaddr_in addr;
	socklen_t len;

	len = sizeof(addr);
	getsockname(fd, (struct sockaddr *)&addr, &len);
	return (ntohs(addr.sin_port));
}
