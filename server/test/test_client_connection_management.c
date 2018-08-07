#include "server.h"

int		test_can_make_server_listener(void)
{
	int fd;

	fd = get_server_socket(4206);
	assert(fd > 0);
	return (0);
}
