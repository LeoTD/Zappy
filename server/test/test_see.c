#include "test.h"
#include "player_type.h"
#include "tile_type.h"
#define GM(x,y) &g_map->tile[x][y]
#include "g_player_list.h"
void	test_see_small(void);
void	test_see_medium(void);
void	test_see_big(void);
void	print_map_info(void);

void	place_resource(int type, int y, int x)
{
	if (type == 6)
		place_food(GM(x,y));
	else
		place_stone(type, GM(x,y));
}

void	fill_row_resources(int y, int x1, int x2, int quantity, int type)
{
	int		copy;

	while (x1 <= x2)
	{
		copy = quantity;
		while (copy-- > 0)
		{
			place_resource(type, y, x1);
		}
			x1++;
	}
}

void	fill_col_resources(int x, int y1, int y2, int quantity, int type)
{
	int		copy;

	while (y1 <= y2)
	{
		copy = quantity;
		while (copy-- > 0)
			place_resource(type, y1, x);
		y1++;
	}
}

void	spin_center(t_player *player)
{
	char *north = "{ player player food food,, food,, linemate sibur, sibur, food sibur, sibur, deraumere sibur,, linemate,, food,, deraumere,, phiras thystame, phiras, linemate phiras, phiras, food phiras, phiras, deraumere phiras, phiras, phiras thystame, phiras thystame, phiras thystame, phiras, linemate phiras, phiras, food phiras, phiras, deraumere phiras, phiras, phiras thystame, phiras thystame,, thystame, thystame,, linemate,, food,, deraumere,, thystame, thystame,, deraumere mendiane, mendiane, mendiane thystame, mendiane thystame, mendiane, linemate mendiane, mendiane, food mendiane, mendiane, deraumere mendiane, mendiane, mendiane thystame, mendiane thystame, mendiane, linemate mendiane }\n";
	char *east = "{ player player food food,, food,, deraumere sibur, deraumere, food deraumere, deraumere, deraumere mendiane,, sibur,, food,, mendiane,, phiras thystame, thystame, sibur thystame, thystame, food thystame, thystame, mendiane thystame, thystame, phiras thystame, phiras thystame, phiras thystame, thystame, sibur thystame, thystame, food thystame, thystame, mendiane thystame, thystame, phiras thystame, phiras thystame,, phiras, phiras,, sibur,, food,, mendiane,, phiras, phiras,, linemate mendiane, linemate, linemate phiras, linemate phiras, linemate, linemate sibur, linemate, food linemate, linemate, linemate mendiane, linemate, linemate phiras, linemate phiras, linemate, linemate sibur }\n";
	char *south = "{ player player food food,, food,, deraumere mendiane, mendiane, food mendiane, mendiane, linemate mendiane,, deraumere,, food,, linemate,, phiras thystame, phiras, deraumere phiras, phiras, food phiras, phiras, linemate phiras, phiras, phiras thystame, phiras thystame, phiras thystame, phiras, deraumere phiras, phiras, food phiras, phiras, linemate phiras, phiras, phiras thystame, phiras thystame,, thystame, thystame,, deraumere,, food,, linemate,, thystame, thystame,, linemate sibur, sibur, sibur thystame, sibur thystame, sibur, deraumere sibur, sibur, food sibur, sibur, linemate sibur, sibur, sibur thystame, sibur thystame, sibur, deraumere sibur }\n";
	char *west = "{ player player food food,, food,, linemate mendiane, linemate, food linemate, linemate, linemate sibur,, mendiane,, food,, sibur,, phiras thystame, thystame, mendiane thystame, thystame, food thystame, thystame, sibur thystame, thystame, phiras thystame, phiras thystame, phiras thystame, thystame, mendiane thystame, thystame, food thystame, thystame, sibur thystame, thystame, phiras thystame, phiras thystame,, phiras, phiras,, mendiane,, food,, sibur,, phiras, phiras,, deraumere sibur, deraumere, deraumere phiras, deraumere phiras, deraumere, deraumere mendiane, deraumere, food deraumere, deraumere, deraumere sibur, deraumere, deraumere phiras, deraumere phiras, deraumere, deraumere mendiane }\n";
	assert(!strcmp(see(player->id, NULL), north));
	right(player->id, NULL);
	assert(!strcmp(see(player->id, NULL), east));
	right(player->id, NULL);
	assert(!strcmp(see(player->id, NULL), south));
	right(player->id, NULL);
	assert(!strcmp(see(player->id, NULL), west));
	right(player->id, NULL);
	assert(!strcmp(see(player->id, NULL), north));
}

void	test_see_medium(void)
{
	game_init(2, 2, 1, 0);
	t_player *p1 = new_player_on_tile(0, 0, 1);
	t_player *p2 = new_player_on_tile(0, 1, 1);
	p1->facing = EAST;
	p1->level = 1;

	char *expect = "{,, player, }\n";
	char *got = see(p1->id, NULL);
	assert(!strcmp(got, expect));
}

void	test_see_small(void)
{
	game_init(1, 1, 1, 0);
	t_player *p1 = new_player_on_tile(0, 0, 0);
	t_player *p2 = new_player_on_tile(0, 0, 0);
	t_player *p3 = new_player_on_tile(0, 0, 0);

	p1->facing = NORTH;
	p1->level = 1;

	fill_col_resources(0, 0, 0, 1, 0);
	fill_col_resources(0, 0, 0, 1, 1);
	fill_col_resources(0, 0, 0, 1, 2);
	fill_col_resources(0, 0, 0, 1, 3);
	fill_col_resources(0, 0, 0, 1, 4);
	fill_col_resources(0, 0, 0, 1, 5);
	fill_col_resources(0, 0, 0, 1, 6);

	char *expect = "{ player player food linemate deraumere sibur mendiane phiras thystame, player player food linemate deraumere sibur mendiane phiras thystame, player player food linemate deraumere sibur mendiane phiras thystame, player player food linemate deraumere sibur mendiane phiras thystame }\n";

	char *got = see(p1->id, NULL);
	assert(!strcmp(got, expect));
}

void	test_see_center(void)
{
	game_init(9, 9, 1, 0);
	t_player *p1 = new_player_on_tile(0, 4, 4);
	t_player *p2 = new_player_on_tile(0, 4, 4);
	t_player *p3 = new_player_on_tile(0, 4, 4);
	p1->facing = NORTH;
	p1->level = 7;

	fill_col_resources(4, 0, 8, 1, 6);
	fill_row_resources(4, 0, 8, 1, 6);
	fill_col_resources(2, 0, 8, 1, 0);
	fill_col_resources(6, 0, 8, 1, 1);
	fill_row_resources(2, 0, 8, 1, 2);
	fill_row_resources(6, 0, 8, 1, 3);

	fill_row_resources(0, 0, 8, 1, 4);
	fill_row_resources(8, 0, 8, 1, 4);
	fill_col_resources(0, 0, 8, 1, 5);
	fill_col_resources(8, 0, 8, 1, 5);

	spin_center(p1);

}
void	test_user_command_see(void)
{
	test_see_small();
	test_see_medium();
	test_see_center();
	printf("%s: ok\n", __func__);
}
