#include "server.h"
#include "player_type.h"

static int      *dead_pids = NULL;
static int      dead_num = 0;

void        reset_obituary(void)
{
    free(dead_pids);
    dead_pids = calloc(1, sizeof(int));
    dead_num = 0;
}

int         *get_dead_players(int *size)
{

}

int         kill_active_player(int pid)
{
    t_player    *p;

    p = get_player(pid);
    g_map->players -= 1;
    g_map->players_on_team[p->team_id] -= 1;
    delete_player_from_list(p);
    return (0);
}