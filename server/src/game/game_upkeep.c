#include "server.h"
#include "player_type.h"

void        feed_inactive_players(int teams)
{
    int         i;
    t_plist     *curr;

    i = -1;
    while (++i < teams)
    {
        curr = g_map->empty_avatars[i];
        while (curr != NULL)
        {
            curr->p->energy;
            if (curr->p->energy <= 0)
            {
                if (curr->p->food > 0)
                {
                    curr->p->food--;
                    curr->p->energy += ENERGY_PER_FOOD;
                }
                else
                    kill_inactive_player(curr->p);
            }
            curr = curr->next;
        }
    }
}

void        feed_active_players(int list_size, int players)
{
    int         i;
    int         pid;
    t_player    *p;

    i = -1;
    pid = 1;
    while (i < players && pid < list_size)
    {
        if ((p = get_player(pid)) != NULL)
        {
            p->energy--;
            if (p->energy <= 0)
            {
                if (p->food > 0)
                {
                    p->food--;
                    p->energy += ENERGY_PER_FOOD;
                }
                else
                    kill_active_player(pid);
            }
            i++;
        }
        pid++;
    }
}

void        game_upkeep(void)
{
    reset_obituary();
    feed_active_players(get_player_list_size(), g_map->players);
    feed_inactive_players(g_map->teams);
}