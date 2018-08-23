#include "server.h"
#include "test.h"
#include "tile_type.h"

char system_sprintf_buf[4096] = { 0 };

void test_server_listen(void)
{
	socket_lookup_init(1);
	g_opts.world_width = 23;
	g_opts.world_height = 19;
	g_opts.teamcount = 3;
	g_opts.team_names = calloc(4, sizeof(char *));
	g_opts.team_names[1] = "zerg";
	g_opts.team_names[0] = "protoss";
	g_opts.team_names[2] = "terran";
	g_opts.initial_players_per_team = 2;
	game_init(g_opts.world_width, g_opts.world_height,
			g_opts.teamcount, g_opts.initial_players_per_team);
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
void           print_map_info(void)
{
	t_tile      *t;
	int         x, y;

	x = -1;
	y = -1;
	while (++x < g_map->dim.x)
	{
		while (++y < g_map->dim.y)
		{
			t = &g_map->tile[x][y];
			printf("(%d, %d)", t->x, t->y);
			printf(" \tStones: [  %d,  %d,  %d,  %d,  %d,  %d ]", t->stones[0], t->stones[1], t->stones[2], t->stones[3], t->stones[4], t->stones[5]);
			printf(" Food: [ %d ] Players: %d", t->food, t->num_players);
			printf("\n");
		}
		y = -1;
	}
}
