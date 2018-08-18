#include "server.h"
#include "test.h"

void test_creates_listen_port(void)
{
	test_server_listen();
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

int random_fake_clients(fd_set *yesdata, fd_set *nodata, int nclients, int *yescount)
{
	int fd;
	int maxfd = 0;
	assert(nclients <= MAX_CLIENTS);
	socket_lookup_init(0);
	FD_ZERO(yesdata);
	FD_ZERO(nodata);
	int actual_yescount = 0;
	int rand;
	for (int i = 0; i < nclients; i++)
	{
		rand = random() % nclients;
		if (rand < *yescount)
		{
			fd = open("somefile", O_RDWR | O_CREAT);
			FD_SET(fd, yesdata);
			++actual_yescount;
		}
		else
		{
			fd = socket(PF_INET, SOCK_STREAM, 0);
			FD_SET(fd, nodata);
		}
		if (fd > maxfd)
			maxfd = fd;
		socket_lookup_add(fd, ACTIVE_PLAYER);
	}
	*yescount = actual_yescount;
	return maxfd;
}

int	do_sockiter_test(fd_set *yes, int yescount, int max)
{
	int cycles = 0;
	clock_t begin = clock();

	for (int i = 0; i < 300000; i++)
	{
		int fd = iter_next_readable_socket();
		if (i % (yescount + 1) == yescount)
		{
			if (fd != -1)
			{
				printf("do_sockiter_test: %d != -1\n", fd);
				return (-1);
			}
			++cycles;
		}
		else
		{
			if (!(FD_ISSET(fd, yes)))
			{
				printf("do_sockiter_test: %d not in readable set\n", fd);
				return (-1);
			}
		}
	}
	while (iter_next_readable_socket() != -1)
		;
	++cycles;
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("iterated fd range (0..%d) %d times at %.8f sec/cycle\n", max + 1, cycles, time_spent / cycles);
	return (0);
}

void test_can_iterate_through_readable_sockets()
{
	fd_set yesdata, nodata;
	int yescount = MAX_CLIENTS;
	int nclients = MAX_CLIENTS;
	int maxfd = random_fake_clients(&yesdata, &nodata, nclients, &yescount);
	do_sockiter_test(&yesdata, yescount, maxfd);
}


void test_client_connection_listener(void)
{
	test_creates_listen_port();
	test_remembers_server_socket();
	test_can_iterate_through_readable_sockets();
}
