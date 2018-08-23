#include "server.h"
#include "player_type.h"
#include "tile_type.h"

void	init_user_commands_test_gamestate(void);

void	test_user_command_inventory(void)
{
	init_user_commands_test_gamestate();
	t_player *p1 = g_map->tile[1][0].players[0];
	t_player *p2 = g_map->tile[2][0].players[0];

	p1->food = 1;
	p1->stones[0] = 1;
	p1->stones[1] = 2;
	p1->stones[2] = 0;
	p1->stones[3] = 4;
	p1->stones[4] = 5;
	p1->stones[5] = 6;
	printf("%s\n", inventory(p1->id, NULL));
}
