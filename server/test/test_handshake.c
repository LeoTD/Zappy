#include "server.h"
#include "test.h"

void test_sends_welcome_message(void)
{
	test_server_listen();
	struct timeval timeout = { .tv_sec = 0, .tv_usec = 2000000 };
	fd_set readable;
	fd_set master;
	FD_ZERO(&master);
	FD_ZERO(&readable);
	FD_SET(get_server_fd(), &master);
	char cmd[256] = { 0 };
	if (!fork())
	{
		fork_and_call_system("nc localhost %d > client_received.txt", get_server_port());
		while (1)
		{
			readable = master;
			select(get_server_fd() + 1, &readable, NULL, NULL, &timeout);
			if (FD_ISSET(get_server_fd(), &readable))
			{
				handle_waiting_connection_data(get_server_fd());
				assert(string_equal_file_contents("WELCOME\n", "client_received.txt"));
				exit(0);
			}
		}
		exit(0);
	}
}

void do_client_completion_test(char *test_teamname, char *expect)
{
	test_server_listen();
	int port = get_server_port();
	char cmd[256] = { 0 };
	int fd;
	fork_and_call_system("echo %s | nc localhost %d > client_received.txt", test_teamname, get_server_port());
	nanosleep(&(struct timespec){ 0, 100000000 }, NULL);
	while ((fd = iter_next_readable_socket()) == -1)
		;
	initiate_user_connection_handshake(fd);
	while ((fd = iter_next_readable_socket()) != -1)
		;
	while ((fd = iter_next_readable_socket()) == -1)
		;
	assert(fd != get_server_fd());
	complete_user_connection_handshake(fd);
	assert(string_equal_file_contents(expect, "client_received.txt"));
}

void test_completing_handshake_with_one_client(void)
{
	char result[256];
	char ok[256] = { 0 };
	sprintf(ok, "WELCOME\n%d\n%d %d\n", 2, g_opts.world_width, g_opts.world_height);
	do_client_completion_test("zerg", ok);
	do_client_completion_test("notateam", "WELCOME\n");
}


void test_handshake(void)
{
	test_sends_welcome_message();
	test_completing_handshake_with_one_client();
	printf("%s: ok\n", __FILE__);
}
