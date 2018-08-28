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
	else if (type == 0)
		place_stone(0, GM(x,y));
	else if (type == 1)
		place_stone(1, GM(x,y));
	else if (type == 2)
		place_stone(2, GM(x,y));
	else if (type == 3)
		place_stone(3, GM(x,y));
	else if (type == 4)
		place_stone(4, GM(x,y));
	else if (type == 5)
		place_stone(5, GM(x,y));
}

void	fill_row_resources(int y, int x1, int x2, int quantity, int type)
{
	int		copy;

	while (x1 <= x2)
	{
		copy = quantity;
		while (copy-- > 0)
		{
		//	printf("placing at: %d %d", x1, y);
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

void	spin(t_player *player)
{
	printf("%s\n", see(player->id, NULL));
	right(player->id, NULL);
	printf("%s\n", see(player->id, NULL));
	right(player->id, NULL);
	printf("%s\n", see(player->id, NULL));
	right(player->id, NULL);
	printf("%s\n", see(player->id, NULL));
	right(player->id, NULL);
	printf("%s\n", see(player->id, NULL));
}

/*
**	Direction
**	Levels
**	Correct tiles
*/
/*
void	test_see_big(void)
{
	int mapx = 18;
	int mapy = 18;
	game_init(mapx, mapy, 1, 0);
	
	t_player *p1 = new_player_on_tile(0, 1, 0);
	g_player_list[0] = p1;
	p1->id = 0;
	p1->facing = SOUTH;

}
*/
// #define GM(x,y) &g_map->tile[x][y]
// game_init(x, y, number_of_teams, number_of_players_per_team
//
void	test_see_medium(void)
{
	game_init(18, 18, 1, 0);
	t_player *p1 = new_player_on_tile(0, 9, 1);
	t_player *p2 = new_player_on_tile(0, 0, 0);
	t_player *p3 = new_player_on_tile(0, 0, 0);
	g_player_list[0] = p1;
	g_player_list[1] = p2;
	g_player_list[2] = p3;
	p1->id = 0;
	p2->id = 1;
	p3->id = 2;
	p1->facing = SOUTH;
	p1->level = 7;


	fill_row_resources(2, 8, 10, 1, 0);	
	fill_row_resources(3, 7, 11, 1, 1);	
	fill_row_resources(4, 6, 12, 1, 2);	
	fill_row_resources(5, 5, 13, 1, 3);	
	fill_row_resources(6, 4, 14, 1, 4);	
	fill_row_resources(7, 3, 15, 1, 5);	
	fill_row_resources(8, 0, 0, 1, 6);
	
	printf("%s\n", see(p1->id, NULL));

//	printf("expected result :\n");
//	print_map_info();


//	spin(p1);

}

void	test_see_small(void)
{
	game_init(1, 1, 1, 0);
	t_player *p1 = new_player_on_tile(0, 0, 0);
	t_player *p2 = new_player_on_tile(0, 0, 0);
	t_player *p3 = new_player_on_tile(0, 0, 0);
	g_player_list[0] = p1;
	g_player_list[1] = p2;
	g_player_list[2] = p3;
	p1->id = 0;
	p2->id = 1;
	p3->id = 2;
	p1->facing = NORTH;
	p1->level = 2;

	fill_col_resources(0, 0, 0, 1, 0);	
	fill_col_resources(0, 0, 0, 1, 1);	
	fill_col_resources(0, 0, 0, 1, 2);	
	fill_col_resources(0, 0, 0, 1, 3);	
	fill_col_resources(0, 0, 0, 1, 4);	
	fill_col_resources(0, 0, 0, 1, 5);	
	fill_col_resources(0, 0, 0, 1, 6);

	printf("expected result :\n");
	print_map_info();

	spin(p1);

}

void	test_see_blindspot(void)
{
	game_init(5, 5, 1, 0);
	t_player *p1 = new_player_on_tile(0, 0, 0);
	t_player *p2 = new_player_on_tile(0, 0, 0);
	t_player *p3 = new_player_on_tile(0, 0, 0);
	g_player_list[0] = p1;
	g_player_list[1] = p2;
	g_player_list[2] = p3;
	p1->id = 0;
	p2->id = 1;
	p3->id = 2;
	p1->facing = NORTH;
	p1->level = 2;

	fill_col_resources(0, 0, 0, 1, 0);	
	fill_col_resources(0, 0, 0, 1, 1);	
	fill_col_resources(0, 0, 0, 1, 2);	
	fill_col_resources(0, 0, 0, 1, 3);	
	fill_col_resources(0, 0, 0, 1, 4);	
	fill_col_resources(0, 0, 0, 1, 5);	
	fill_col_resources(0, 0, 0, 1, 6);

	printf("expected result :\n");
	print_map_info();

	spin(p1);

}

void	test_see_center(void)
{
	game_init(9, 9, 1, 0);
	t_player *p1 = new_player_on_tile(0, 4, 4);
	t_player *p2 = new_player_on_tile(0, 4, 4);
	t_player *p3 = new_player_on_tile(0, 4, 4);
	g_player_list[0] = p1;
	g_player_list[1] = p2;
	g_player_list[2] = p3;
	p1->id = 0;
	p2->id = 1;
	p3->id = 2;
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
//	test_see_small();
//	test_see_medium();
//	test_see_blindspot();
	test_see_center();
	printf("%s: ok\n", __func__);	
}
