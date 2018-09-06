#include "server.h"
#include "player_type.h"
#include "command_queue_type.h"
#include "command_type.h"
#include "client_type.h"
#include "incantation.h"

struct s_incant_req		g_incant_reqs[7] =
{
	{ 1, { 1, 0, 0, 0, 0, 0 } },
	{ 2, { 1, 1, 1, 0, 0, 0 } },
	{ 2, { 2, 0, 1, 0, 2, 0 } },
	{ 4, { 1, 1, 2, 0, 1, 0 } },
	{ 4, { 1, 2, 1, 3, 0, 0 } },
	{ 6, { 1, 2, 3, 0, 1, 0 } },
	{ 6, { 2, 2, 2, 2, 2, 1 } }
};

int						incantatation_succeeds(int priest_level, int group_size,
												int *stones)
{
	int i;

	if (priest_level == 8)
		return (0);
	if (group_size < g_incant_reqs[priest_level - 1].group_size)
		return (0);
	i = 0;
	while (i < 6)
	{
		if (stones[i] < g_incant_reqs[priest_level - 1].stones[i])
			return (0);
		++i;
	}
	return (1);
}

/*
** `select_players_at_level` modifies the passed `player_ids` array, moving
** the ids matching `level` to the front.
** It returns the number of matches it found.
**
** (In this example, only players 2, 5 and 6 are level 1.)
** `int player_ids[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };`
** `hits = select_players_at_level(1, player_ids, 9);`
**     --> hits == 3, player_ids: {6, 5, 2, 3, 4, 1, 7, 8, 0 }
*/

int						select_players_at_level(int level, int *player_ids,
												int num_ids)
{
	int hits;
	int misses;
	int	id;

	hits = 0;
	misses = 0;
	while (hits + misses < num_ids)
	{
		id = player_ids[hits];
		if (get_player(id) && get_player(id)->level == level)
			++hits;
		else
		{
			player_ids[hits] = player_ids[num_ids - misses - 1];
			player_ids[num_ids - misses - 1] = id;
			++misses;
		}
	}
	return (hits);
}

char					*incantation_finish(int player_id, void *args)
{
	t_player				*player;
	int						i;
	struct s_incant_args	*incant_args;
	char					*response;

	(void)player_id;
	incant_args = (struct s_incant_args *)args;
	i = 0;
	while (i < incant_args->group_size)
	{
		player = get_player(incant_args->levelup_group[i]);
		if (player != NULL && player->level < incant_args->new_level)
			increase_player_level(player, incant_args->new_level);
		++i;
	}
	asprintf(&response, "current level %d\n", incant_args->new_level);
	return (response);
}

struct s_incant_args	*create_incant_attempt_args(int pid)
{
	int						*tile_player_ids;
	int						group_size;
	int						priest_level;
	struct s_incant_args	*result;
	int						*stones;

	assert(get_player(pid));
	priest_level = get_player(pid)->level;
	tile_player_ids = get_current_tile_player_count(pid, &group_size);
	stones = get_current_tile_stones(pid);
	result = malloc(sizeof(*result));
	group_size = select_players_at_level(
			priest_level, tile_player_ids, group_size);
	result->player_id = pid;
	if (incantatation_succeeds(priest_level, group_size, stones))
	{
		result->new_level = priest_level + 1;
		result->group_size = group_size;
		remove_stones(g_incant_reqs[priest_level - 1].stones,
				get_player(pid)->tile);
	}
	else
	{
		result->new_level = priest_level;
		result->group_size = 1;
	}
	result->levelup_group = tile_player_ids;
	free(stones);
	return (result);
}

char					*incantation(int player_id, void *args)
{
	t_command				*finish;
	t_command_queue			*q;

	(void)args;
	finish = new_cmd(incantation_finish);
	finish->args = (char *)create_incant_attempt_args(player_id); // FIXME: change everything to void *
	finish->player_id = player_id;
	q = get_client_by_player_id(player_id)->cmdqueue;
	if (q->remaining_space < MAX_COMMANDS)
		q->remaining_space += 1;
	enqueue_front(q, finish);
	return ("elevation in progress\n");
}
