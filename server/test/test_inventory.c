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
	p1->stones[0] = 1;
	p1->stones[1] = 2;
	p1->stones[2] = 0;
	p1->stones[3] = 4;
	p1->stones[4] = 5;
	p1->stones[5] = 6;
	printf("%s\n", inventory(p1->id, NULL));
}

void	show_coordinates(t_player *player)
{

}

void	test_user_command_kick(void)
{
	init_user_commands_test_gamestate();
	t_player *p1 = g_map->tile[1][0].players[0];
	t_player *p2 = g_map->tile[2][0].players[0];
	t_player *p3 = new_player_on_tile(0, 1, 0);
	t_player *p4 = new_player_on_tile(0, 1, 0);
	t_player *p6 = new_player_on_tile(0, 1, 0);
	t_player *p5 = new_player_on_tile(0, 1, 0);

	p1->facing = EAST;
	p2->facing = WEST;
//	p3->facing = SOUTH;

	printf("%d | %d\n", p1->tile->num_players, p2->tile->num_players);
	printf("%s\n", kick(p1->id, NULL));
	printf("%d | %d\n", p1->tile->num_players, p2->tile->num_players);
	printf("%s\n", kick(p1->id, NULL));
	printf("%d | %d\n", p1->tile->num_players, p2->tile->num_players);
	printf("%s\n", kick(p2->id, NULL));
	printf("%d | %d\n", p1->tile->num_players, p2->tile->num_players);
	printf("%s\n", kick(p2->id, NULL));
	printf("%d | %d\n", p1->tile->num_players, p2->tile->num_players);
}
