#include "server.h"
#include "player_type.h"
#include "command_queue_type.h"
#include "command_type.h"
#include "client_type.h"
#include "incantation.h"
#include "tile_type.h"

t_objcount	g_incant_reqs[7] =
{
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 2 },
	{ 2, 0, 1, 0, 2, 0, 0, 2 },
	{ 1, 1, 2, 0, 1, 0, 0, 4 },
	{ 1, 2, 1, 3, 0, 0, 0, 4 },
	{ 1, 2, 3, 0, 1, 0, 0, 6 },
	{ 2, 2, 2, 2, 2, 1, 0, 6 }
};

void					construct_totem(t_tile *t, int priest_level)
{
	int		i;

	i = MIN_STONE;
	while (i <= MAX_STONE)
	{
		t->count[i] -= g_incant_reqs[priest_level - 1][i];
		assert(t->count[i] >= 0);
		gfx_sendall("USE_STONE_FOR_TOTEM %d %d\n",
				i, g_incant_reqs[priest_level - 1][i]);
		i++;
	}
}

void					get_ritual_pids(t_player *p, struct s_incant_args *a)
{
	int		i;
	int		j;
	t_tile	*t;

	t = p->tile;
	a->levelup_group = calloc(t->count[PLAYERS], sizeof(int));
	a->group_size = t->count[PLAYERS];
	i = 0;
	j = 0;
	while (i < t->count[PLAYERS])
	{
		if (t->players[i]->level == p->level)
		{
			a->levelup_group[j++] = t->players[i]->id;
		}
		else
			a->group_size -= 1;
		i++;
	}
}

char					*incantation_finish(int player_id, void *args)
{
	t_player				*player;
	int						i;
	struct s_incant_args	*incant_args;
	char					*response;

	incant_args = (struct s_incant_args *)args;
	i = 0;
	gfx_sendall("INCANT_FINISH %d %d\n", player_id, incant_args->new_level);
	while (i < incant_args->group_size)
	{
		player = get_player(incant_args->levelup_group[i]);
		if (player != NULL && player->level < incant_args->new_level)
		{
			increase_player_level(player, incant_args->new_level);
			gfx_sendall("LEVEL_UP %d %d\n", player->id, incant_args->new_level);
		}
		++i;
	}
	gfx_sendall("%s", "DONE\n");
	asprintf(&response, "current level %d\n", get_player(player_id)->level);
	free(incant_args);
	return (response);
}

struct s_incant_args	*create_incant_attempt_args(t_player *priest)
{
	struct s_incant_args	*outcome;
	int						*reqs;

	outcome = malloc(sizeof(*outcome));
	get_ritual_pids(priest, outcome);
	reqs = g_incant_reqs[priest->level - 1];
	if (priest->level < 8
			&& reqs[PLAYERS] <= outcome->group_size
			&& reqs[LINEMATE] <= priest->tile->count[LINEMATE]
			&& reqs[DERAUMERE] <= priest->tile->count[DERAUMERE]
			&& reqs[SIBUR] <= priest->tile->count[SIBUR]
			&& reqs[MENDIANE] <= priest->tile->count[MENDIANE]
			&& reqs[PHIRAS] <= priest->tile->count[PHIRAS]
			&& reqs[THYSTAME] <= priest->tile->count[THYSTAME])
	{
		construct_totem(priest->tile, priest->level);
		outcome->new_level = priest->level + 1;
	}
	else
	{
		outcome->new_level = priest->level;
		outcome->group_size = 1;
	}
	return (outcome);
}

char					*incantation(int player_id, void *args)
{
	t_command				*finish;
	t_ply_cmd_queue			*q;
	int						i;
	struct s_incant_args	*incant_args;

	(void)args;
	gfx_sendall("%s", "INCANT_START\n");
	finish = new_cmd(incantation_finish);
	assert(get_player(player_id));
	incant_args = create_incant_attempt_args(get_player(player_id));
	finish->args = incant_args;
	finish->player_id = player_id;
	q = &(get_client_by_id(player_id)->cmdqueue);
	if (q->size >= MAX_COMMANDS)
		q->size -= 1;
	ply_enqueue_front(q, finish);
	gfx_sendall("LEAD_RITUAL %d %d %d %d\n", player_id, incant_args->new_level > get_player(player_id)->level, incant_args->new_level, incant_args->group_size);
	i = 0;
	while (i < incant_args->group_size)
	{
		if (incant_args->levelup_group[i] != player_id)
			gfx_sendall("JOIN_RITUAL %d\n", incant_args->levelup_group[i]);
		i++;
	}
	gfx_sendall("%s", "DONE\n");
	return ("elevation in progress\n");
}
