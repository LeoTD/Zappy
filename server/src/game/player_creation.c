#include "server.h"
#include "player_type.h"

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

	return (0);
}

/*
** Take a pointer to a [ t_player * ]
** Mallocs and fills the struct with initial values
**
** Usage: player_id = new_player((EGG_TIMER || 0), team_id)
*/

int				get_pid(void)
{
	static int i = -1;

	i = i + 1;
	return (i);
}

t_player		*new_player(int egg, int team_id, int team_pid)
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
	tmp->egg = egg;
	tmp->id = get_pid();
	add_player_to_team_waitlist(tmp);
	return (tmp);
}
