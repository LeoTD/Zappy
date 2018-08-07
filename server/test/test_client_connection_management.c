#include "server.h"
#include "time.h"

int		test_can_make_server_listener(void)
{
	int fd;

	fd = get_server_socket(0);
	assert(fd > 0);
	close(fd);
	return (0);
}

void	quicksleep(void)
{
	struct timespec rqtp;

	rqtp.tv_sec = 0;
	rqtp.tv_nsec = 100000000;
	nanosleep(&rqtp, NULL);
}

int		test_server_listens_for_clients(void)
{
	int		fd;
	struct sockaddr_in	server;
	socklen_t	len;
	char cmd[255] = {0};

	len = sizeof server;
	fd = get_server_socket(0);
	getsockname(fd, (struct sockaddr *)&server, &len);
	sprintf(cmd, "echo 'hello' | nc localhost %d", ntohs(server.sin_port));
	if (!fork())
	{
		close(fd);
		if (!fork())
			system(cmd);
		else
		{
			quicksleep();
			memcpy(cmd + 6, "kill!", 5);
			system(cmd);
		}
	}
	else
	{
		accept_and_poll_clients(fd);
	}
	return (0);
}
