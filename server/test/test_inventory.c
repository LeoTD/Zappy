#include "test.h"
#include "player_type.h"
#include "tile_type.h"

#define ASSERT_OK(x) assert(!strcmp(x, "ok\n"))
#define ASSERT_KO(x) assert(!strcmp(x, "ko\n"))

void	init_user_commands_test_gamestate(void);

void	test_user_command_inventory(void)
{
	init_user_commands_test_gamestate();
	t_player *p1 = g_map->tile[1][0].players[0];
	t_player *p2 = g_map->tile[2][0].players[0];

	p1->food = 1;
	p1->energy = 9000;
	p1->stones[0] = 1;
	p1->stones[1] = 2;
	p1->stones[2] = 0;
	p1->stones[3] = 4;
	p1->stones[4] = 5;
	p1->stones[5] = 6;
	char *result = "{ food 9126, linemate 1, deraumere 2, sibur 0, mendiane 4, phiras 5, thystame 6 }\n";

	assert(!strcmp(inventory(p1->id, NULL), result));
	printf("%s: ok\n", __func__);
}
