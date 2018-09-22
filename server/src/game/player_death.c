#include "server.h"
#include "player_type.h"

#define OBIT_START_SIZE 8

static int		*g_dead_pids = NULL;
static int		g_obit_size = 0;
static int		g_dead_num = 0;

void			reset_obituary(void)
{
	g_dead_num = 0;
}

int				*get_dead_players(int *size)
{
	*size = g_dead_num;
	return (g_dead_pids);
}

void			remove_dead_plist_node(t_player *p)
{
	t_plist		*prev;
	t_plist		*curr;

	if (!g_map->empty_avatars[p->team_id])
		return ;
	if (g_map->empty_avatars[p->team_id]->p == p)
		remove_player_from_waitlist(p->team_id);
	else
	{
		prev = g_map->empty_avatars[p->team_id];
		curr = prev->next;
		while (curr != NULL && curr->p != p)
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr && curr->p == p)
		{
			prev->next = curr->next;
			free(curr);
		}
	}
}

int				kill_player(t_player *p)
{
	if (!g_dead_pids)
		g_dead_pids = calloc((g_obit_size = OBIT_START_SIZE), sizeof(int));
	if (g_dead_num == g_obit_size)
		g_dead_pids = realloc(g_dead_pids, (g_obit_size *= 2) * sizeof(int));
	remove_player_from_tile(p, p->tile);
	g_map->players -= 1;
	g_map->players_on_team[p->team_id] -= 1;
	g_dead_pids[g_dead_num] = p->id;
	g_dead_num++;
	remove_dead_plist_node(p);
	delete_player_from_list(p);
	return (0);
}
