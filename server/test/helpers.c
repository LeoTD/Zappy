#include "server.h"
#include "test.h"

char system_sprintf_buf[4096] = { 0 };

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

int get_server_port(void)
{
	return (get_port_from_fd(get_server_fd()));
}

int string_equal_file_contents(char *expect_string, char *filepath)
{
	size_t bufsize = strlen(expect_string) + 1;
	char *actual = malloc(bufsize);
	bzero(actual, bufsize);
	int fd = open(filepath, O_RDONLY | O_CREAT);
	read(fd, actual, bufsize - 1);
	int success = !strcmp(actual, expect_string);
	free(actual);
	close(fd);
	return success;
}
