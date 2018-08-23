#include "server.h"
#include "player_type.h"
#include "g_player_list.h"

void			cleanup_player_list(void)
{
	free(g_player_list);
}

int             delete_player_from_list(t_player *p)
{
    int         pid;

    pid = p->id;
    free(g_player_list[pid]);
    g_player_list[pid] = NULL;
    return (0);
}

int             get_team_by_player(int pid)
{
    t_player    *p;

    p = get_player(pid);
    return (p->team_id);
}