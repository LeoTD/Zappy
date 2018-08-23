#include "server.h"
#include "player_type.h"
#include "tile_type.h"

/*
** TODO: Takes avatar on team [ team_id ] off the empty avatar list
** 		 Adds that avatar to the active player list.
** 		 returns the player_id.
**
** 		 If no empty avatar is found, returns [ -1 ].
*/

int				assign_avatar(int team_id)
{
	t_player	*new;

	new = remove_player_from_waitlist(team_id);
	if (new == NULL)
		return (-1);
	add_player_to_list(new);
	return (new->id);
}

/*
** Take a pointer to a [ t_player * ]
** Mallocs and fills the struct with initial values
*/

int				get_pid(void)
{
	g_map->pids += 1;
	return (g_map->pids);
}

t_player		*new_player(int team_id, int team_pid)
{
	t_player	*tmp;
	int			i;

	i = -1;
	if ((tmp = malloc(sizeof(t_player))) == NULL)
		ERR_OUT("player creation; malloc");
	tmp->tile = NULL;
	tmp->facing = random() % 4;
	while (++i < 6)
		tmp->stones[i] = 0;
	tmp->food = DEFAULT_FOOD;
	tmp->energy = DEFAULT_ENERGY;
	tmp->level = DEFAULT_LEVEL;
	tmp->team_id = team_id;
	tmp->team_pid = team_pid;
	tmp->id = get_pid();
	add_player_to_team_waitlist(tmp);
	g_map->players++;
	return (tmp);
}

t_player		*new_player_on_tile(int team_id, int x, int y)
{
	t_player	*p;

	p = new_player(team_id, 0); // team_pid not in use
	add_player_to_tile(p, &g_map->tile[x][y]);
	add_player_to_list(p);
	g_map->players_on_team[team_id] += 1;
	g_map->players += 1;
	return (p);
}
