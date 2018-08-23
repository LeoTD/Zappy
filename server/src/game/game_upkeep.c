#include "server.h"
#include "player_type.h"

void        game_upkeep(void)
{
    int         i;
    int         pid;
    t_player    *p;
    int         list_size;

    i = -1;
    pid = 0;
    list_size = get_player_list_size();
    while (i < g_map->players && pid < list_size)
    {
        if ((p = get_player(pid)) != NULL)
        {
            p->energy--;
            if (p->energy < 0)
            {
                if (p->food > 0)
                {
                    p->food--;
                    p->energy += ENERGY_PER_FOOD;
                }
                else
                    kill_player(pid);
            }
            i++;
        }
        pid++;
    }
}