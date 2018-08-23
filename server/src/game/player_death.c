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
    *size = dead_num;
    return (dead_pids);
}

void        remove_dead_plist_node(t_player *p)
{
    t_plist     *prev;
    t_plist     *curr;

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
        if (curr->p == p)
        {
            prev->next = curr->next;
            free(curr);
        }
    }
}

int         kill_inactive_player(t_player *p)
{
    remove_player_from_tile(p, p->tile);
    g_map->players -= 1;
    g_map->players_on_team[p->team_id] -= 1;
    remove_dead_plist_node(p);
    dead_pids = realloc(dead_pids, sizeof(int) * (dead_num + 1));
    dead_pids[dead_num++] = p->id;
    free(p);
    return (0);
}

int         kill_active_player(int pid)
{
    t_player    *p;

    p = get_player(pid);
    remove_player_from_tile(p, p->tile);
    g_map->players -= 1;
    g_map->players_on_team[p->team_id] -= 1;
    dead_pids = realloc(dead_pids, sizeof(int) * (dead_num + 1));
    dead_pids[dead_num++] = p->id;
    delete_player_from_list(p);
    return (0);
}