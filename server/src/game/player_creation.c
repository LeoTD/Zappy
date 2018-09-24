#include "server.h"
#include "player_type.h"
#include "tile_type.h"

#define DEFAULT_FOOD 10
#define DEFAULT_ENERGY 0
#define DEFAULT_LEVEL 1

static int		g_pid_count;

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
	return (new->id);
}

/*
** Take a pointer to a [ t_player * ]
** Mallocs and fills the struct with initial values
*/

void			reset_pid(void)
{
	g_pid_count = 1;
}

t_player		*new_player(int team_id)
{
	t_player	*tmp;
	int			i;
	static int	faceable_directions[4] = { NORTH, EAST, SOUTH, WEST };

	i = -1;
	if ((tmp = malloc(sizeof(t_player))) == NULL)
		ERR_OUT("player creation; malloc");
	bzero(tmp->count, sizeof(tmp->count));
	tmp->tile = NULL;
	tmp->facing = faceable_directions[random() % 4];
	tmp->count[FOOD] = DEFAULT_FOOD;
	tmp->energy = DEFAULT_ENERGY;
	tmp->level = DEFAULT_LEVEL;
	tmp->team_id = team_id;
	tmp->id = g_pid_count++;
	add_player_to_list(tmp);
	add_player_to_team_waitlist(tmp);
	g_map->players++;
	return (tmp);
}

t_player		*new_player_on_tile(int team_id, int x, int y)
{
	t_player	*p;

	p = new_player(team_id);
	add_player_to_tile(p, &g_map->tile[x][y]);
	return (p);
}
