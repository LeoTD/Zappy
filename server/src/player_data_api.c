#include "server.h"

#define START_SIZE 64

static t_player		**g_player_list = NULL;
static int				g_list_size = START_SIZE;

int				grow_list(void)
{
	g_list_size *= 2;
	g_player_list = realloc(g_player_list, sizeof(t_player *) * g_list_size);
	if (!g_player_list)
		ERR_OUT("grow list; realloc");
	return (0);
}

int				add_player_to_list(t_player *t)
{
	if (g_player_list == NULL)
		if ((g_player_list = malloc(sizeof(t_player *) * START_SIZE)) == NULL)
			ERR_OUT("player list; malloc");
	if (t->id >= g_list_size)
		grow_list();
	g_player_list[t->id] = t;
	return (0);
}

t_player		*get_player(int pid)
{
	return (g_player_list[pid]);
}

void			cleanup_player_list(void)
{
	free(g_player_list);
}
