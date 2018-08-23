#include "server.h"
#include "player_type.h"

/*int         *get_dead_players(int *size)
{

}*/

int         kill_player(int pid)
{
    t_player    *p;

    p = get_player(pid);
    g_map->players -= 1;
    g_map->players_on_team[p->team_id] -= 1;
    delete_player_from_list(p);
    return (0);
}