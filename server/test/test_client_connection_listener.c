#include "server.h"
#include "test.h"

int	get_port_from_fd(int fd)
{
	struct sockaddr_in addr;
	socklen_t len;

	len = sizeof(addr);
	getsockname(fd, (struct sockaddr *)&addr, &len);
	return (ntohs(addr.sin_port));
}

void test_creates_listen_port(void)
{
	g_opts.server_port = 0x0;
	listen_for_connections(g_opts.server_port);
	char buf[256] = { 0 };
	int realport = get_port_from_fd(get_server_fd());
	sprintf(buf, "lsof -i :%d > /dev/null && echo port %d listening || echo %s failed",
		realport, realport, __func__);
	system(buf);
}

void test_remembers_server_socket(void)
{
	assert(get_server_fd() != -1);
}

void	quicksleep(void)
{
	struct timespec rqtp;

	rqtp.tv_sec = 0;
	rqtp.tv_nsec = 100000000;
	nanosleep(&rqtp, NULL);
}

void test_sends_welcome_message(void)
{
	struct timeval timeout = { .tv_sec = 0, .tv_usec = 2000000 };
	fd_set readable;
	fd_set master;
	FD_ZERO(&master);
	FD_ZERO(&readable);
	FD_SET(get_server_fd(), &master);
	char cmd[256] = { 0 };
	if (!fork())
	{
		if (!fork())
		{
			sprintf(cmd, "nc localhost %d > client_received.txt", get_port_from_fd(get_server_fd()));
			system(cmd);
			exit(0);
		}
		while (1)
		{
			readable = master;
			select(get_server_fd() + 1, &readable, NULL, NULL, &timeout);
			if (FD_ISSET(get_server_fd(), &readable))
			{
				handle_waiting_connection_data(get_server_fd());
				system("cat client_received.txt");
				exit(0);
			}
		}
		exit(0);
	}
}


void test_client_connection_listener(void)
{
	test_creates_listen_port();
	test_remembers_server_socket();
	test_sends_welcome_message();
}
