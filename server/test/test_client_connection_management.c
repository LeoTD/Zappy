#include "server.h"
#include "time.h"

int		test_can_make_server_listener(void)
{
	listen_for_connections(8282);
	return (0);
}

void	quicksleep(void)
{
	struct timespec rqtp;

	rqtp.tv_sec = 0;
	rqtp.tv_nsec = 100000000;
	nanosleep(&rqtp, NULL);
}

int g_make_server_die = 0;

int		test_server_listens_for_clients(void)
{
	int		serv_fd = 8283;
	int		readable_socket;
	struct sockaddr_in	server;
	socklen_t	len;
	char cmd[255] = {0};

	len = sizeof server;
	listen_for_connections(serv_fd);
	HEREMSG;
	getsockname(serv_fd, (struct sockaddr *)&server, &len);
	sprintf(cmd, "echo 'hello' | nc localhost %d", ntohs(server.sin_port));
	if (!fork())
	{
		close(serv_fd);
		if (!fork())
		{
			system(cmd);
			exit(0);
		}
		else
		{
			quicksleep();
			memcpy(cmd + 6, "kill!", 5);
			system(cmd);
		}
		exit(0);
	}
	else
	{
		while (1)
		{
	HEREMSG;
			while ((readable_socket = get_socket_with_available_data()) != -1)
			{
	HEREMSG;
				handle_waiting_connection_data(readable_socket);
			}
			if (g_make_server_die)
			{
				printf("%s: ok\n", __func__);
				break;
			}
		}
	}
	return (0);
}
