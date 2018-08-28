#include "incantation.h"
#include "test.h"
#include "g_player_list.h"

int		select_players_at_level();
struct	s_incant_args *create_incant_attempt_args(int pid);

void	do_select_players_test(int level, int *player_ids, int start_size,
								int *expected_player_ids, int expected_size)
{
	int result_size = select_players_at_level(level, player_ids, start_size);
	assert(result_size == expected_size);
	for (int i = 0; i < expected_size; i++)
	{
		int found = 0;
		for (int j = 0; j < expected_size; j++)
		{
			if (player_ids[j] == expected_player_ids[i])
			{
				assert(found == 0);
				found = 1;
			}
		}
		assert(found == 1);
	}
}

void	test_can_select_players_with_same_level(void)
{
#define TEST_SELECT_OG_GROUP_SIZE 9
	game_init(1, 1, 3, 3);
	int pids[TEST_SELECT_OG_GROUP_SIZE];
	int store[TEST_SELECT_OG_GROUP_SIZE];
	int group_size = TEST_SELECT_OG_GROUP_SIZE;
	for (int i = 0; i < group_size; i++)
	{
		t_player *p = new_player_on_tile(0, 0, 0);
		store[i] = p->id;
		if (i == 2 || i == 4 || i == 7)
			p->level = 3;
		if (i == 0)
			p->level = 8;
	}
	memcpy(pids, store, sizeof(store));
	int want1[] = { pids[2], pids[4], pids[7] };
	do_select_players_test(3, pids, group_size, want1, 3);

	memcpy(pids, store, sizeof(store));
	int want2[] = { pids[1], pids[3], pids[5], pids[6], pids[8] };
	do_select_players_test(1, pids, group_size, want2, 5);

	memcpy(pids, store, sizeof(store));
	int want3[] = { pids[0] };
	do_select_players_test(8, pids, group_size, want3, 1);
}

void	do_incant_args_creation_test(int *levels, int num_players,
			int stones[6], int should_succeed)
{
	game_init(1, 1, 1, num_players);
	for (int i = 0; i < num_players; i++)
		assign_avatar(0);
	int _nothing;
	int *pids = get_current_tile_player_count(lowest_active_player_id(),
			&_nothing);
	for (int i = 0; i < num_players; i++)
	{
		assert(get_player(pids[i]));
		get_player(pids[i])->level = levels[i];
	}
	memcpy(g_map->tile[0][0].stones, stones, sizeof(int) * 6);
	int priest_id = pids[0];
	struct s_incant_args *result = create_incant_attempt_args(priest_id);
	if (should_succeed)
	{
		assert(get_player(priest_id));
		assert(result->new_level == get_player(priest_id)->level + 1);
		if (levels[0] > 1)
			assert(result->group_size > 1);
		assert(memcmp(stones, g_map->tile[0][0].stones, sizeof(int) * 6) != 0);
	}
	else
	{
		assert(get_player(priest_id));
		assert(result->new_level == get_player(priest_id)->level);
		assert(result->group_size == 1);
		assert(!memcmp(stones, g_map->tile[0][0].stones, sizeof(int) * 6));
	}
}

void	test_creates_correct_incant_args(void)
{
	int playerlevels[] = {
		-1, // put real guy here
		1,
		2, 2,
		3, 3,
		4, 4, 4, 4,
		5, 5, 5, 5,
		6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7,
		8
	};
	int lotsofstones[6] = { 99, 99, 99, 99, 99, 99 };
	int num_players  = (sizeof(playerlevels) / sizeof(*(playerlevels)));

	// pass because there's tons of everything:
	for (int i = 1; i < 8; i++)
	{
		playerlevels[0] = i;
		do_incant_args_creation_test(playerlevels, num_players, lotsofstones, 1);
	}
	// fail because not enough players at correct level:
	do_incant_args_creation_test((int []){ 2 }, 1, lotsofstones, 0);
	do_incant_args_creation_test((int []){ 3 }, 1, lotsofstones, 0);
	do_incant_args_creation_test((int []){ 4, 4, 4 }, 3, lotsofstones, 0);
	do_incant_args_creation_test((int []){ 5, 5, 5 }, 3, lotsofstones, 0);
	do_incant_args_creation_test((int []){ 6, 6, 6, 6, 6 }, 5, lotsofstones, 0);
	do_incant_args_creation_test((int []){ 7, 7, 7, 7, 7 }, 5, lotsofstones, 0);
	//fail because can't level past 8:
	do_incant_args_creation_test((int []){ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}, 10, lotsofstones, 0);

	// fail because not enough stones:
	lotsofstones[0] = 0;
	for (int i = 1; i < 8; i++)
	{
		playerlevels[0] = i;
		do_incant_args_creation_test(playerlevels, num_players, lotsofstones, 0);
	}
}

void	test_incantation_start_to_finish(int should_succeed)
{
	struct s_incant_args *a;
	int num_players = 8;
	int priest_level = 4;
	int new_level = priest_level + !!should_succeed;

	game_init(1, 1, 1, num_players);
	for (int i = 0; i < num_players; i++)
		assign_avatar(0);
	int _nothing;
	int *pids = get_current_tile_player_count(lowest_active_player_id(),
			&_nothing);
	for (int i = 0; i < num_players; i++)
	{
		assert(get_player(pids[i]));
		if (i % 2 == 0)
			get_player(pids[i])->level = priest_level;
		else
			get_player(pids[i])->level = 1;
	}
	int stones[] = { 1, 1, 2, 0, 1, 0 };
	if (should_succeed == 0)
		--stones[2];
	memcpy(g_map->tile[0][0].stones, stones, sizeof(int) * 6);
	a = create_incant_attempt_args(pids[0]);
	char *response = incantation_finish(pids[0], a);
	char *expected;
	asprintf(&expected, "current level %d\n", new_level);
	assert(!strcmp(response, expected));
	for (int i = 0; i < num_players; i++)
	{
		assert(get_player(pids[i]));
		if (i % 2 == 0)
			assert(get_player(pids[i])->level == new_level);
		else
			assert(get_player(pids[i])->level == 1);
	}
}

void	test_user_command_incantation(void)
{
	test_can_select_players_with_same_level();
	test_creates_correct_incant_args();
	test_incantation_start_to_finish(1);
	test_incantation_start_to_finish(0);
	printf("%s: ok\n", __FILE__);
}
