#include "server.h"
#include "test.h"

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

void test_accepts_valid_teamnames(void)
{
	int port = get_port_from_fd(get_server_fd());
	char buf[256] = { 0 };
	char *tn[] = { "zerg", "protoss", "terran", NULL };
	struct s_opts g_opts = { .team_names = (char*[]){ "zerg", "protoss", "terran", NULL } };
	int fd;
	while (1)
	{
		while ((fd = iter_next_readable_socket()) != -1)
		{
			if (fd != get_server_fd())
			{
				handle_waiting_connection_data(fd);
				exit(0);
			}
		}
	}
}

void test_handshake(void)
{
	socket_lookup_init(1);
	g_opts.server_port = 0x0;
	listen_for_connections(g_opts.server_port);
	test_sends_welcome_message();
}
