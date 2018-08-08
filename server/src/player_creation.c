#include "server.h"

/*
** Take a pointer to a [ t_player * ]
** Mallocs and fills the struct with initial values
** TODO: Adds player to team-specific empty avatar list
** TODO: get_team_pid() (ex. player [ 1 ], on team 2)
**
** Usage: player_id = new_player(start_tile, (EGG_TIMER || 0), team_id)
*/

int TEMP_get_pid(void)
{
	static int i = 0;
	return (--i);
}

t_player		*new_player(int egg, int team_id)
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
	tmp->team = team_id;
	tmp->team_pid = 0; //Get_team_pid() ???
	tmp->egg = egg;
	tmp->id = TEMP_get_pid();

	add_player_to_empty_list(tmp, tmp->team);

	return (tmp);
}

/*
** TODO: Adds player to empty avatar list for [ team ].
*/

int				add_player_to_empty_list(t_player *p, int team)
{
	p = 0;
	team = 0;
	return (0);
}
