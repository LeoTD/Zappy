#include "test.h"
#include "player_type.h"
#include "tile_type.h"
#include <assert.h>

char	*find_kick_origin(int kick_dir, int player_dir);

void	init_user_commands_test_gamestate(void);

void	test_user_command_kick(void)
{
	game_init(2, 2, 1, 0);
	
	t_player *p1 = new_player_on_tile(0, 0, 0);
	t_player *p2 = new_player_on_tile(0, 1, 0);
	t_player *p3 = new_player_on_tile(0, 1, 1);
	t_player *p4 = new_player_on_tile(0, 0, 1);
	p1->facing = EAST;
	p2->facing = SOUTH;
	p3->facing = WEST;
	p4->facing = NORTH;
	

	t_player *p5 = new_player_on_tile(0, 0, 0);
	t_player *p6 = new_player_on_tile(0, 0, 0);
	t_player *p7 = new_player_on_tile(0, 0, 0);
	t_player *p8 = new_player_on_tile(0, 0, 0);
	p5->facing = NORTH;
	p6->facing = WEST;
	p7->facing = SOUTH;
	p8->facing = EAST;
	register_user_client(5, p5->id);
	register_user_client(6, p6->id);
	register_user_client(7, p7->id);
	register_user_client(8, p8->id);

	
	assert(!strcmp(find_kick_origin(p1->facing, p5->facing), "moving <3>\n"));
	assert(!strcmp(find_kick_origin(p1->facing, p6->facing), "moving <1>\n"));
	assert(!strcmp(find_kick_origin(p1->facing, p7->facing), "moving <7>\n"));
	assert(!strcmp(find_kick_origin(p1->facing, p8->facing), "moving <5>\n"));

	assert(!strcmp(kick(p1->id, NULL), "ok\n"));
	assert(!strcmp(kick(p1->id, NULL), "ko\n"));
	
	assert(!strcmp(find_kick_origin(p2->facing, p5->facing), "moving <1>\n"));
	assert(!strcmp(find_kick_origin(p2->facing, p6->facing), "moving <7>\n"));
	assert(!strcmp(find_kick_origin(p2->facing, p7->facing), "moving <5>\n"));
	assert(!strcmp(find_kick_origin(p2->facing, p8->facing), "moving <3>\n"));

	assert(!strcmp(kick(p2->id, NULL), "ok\n"));
	assert(!strcmp(kick(p2->id, NULL), "ko\n"));
	
	assert(!strcmp(find_kick_origin(p3->facing, p5->facing), "moving <7>\n"));
	assert(!strcmp(find_kick_origin(p3->facing, p6->facing), "moving <5>\n"));
	assert(!strcmp(find_kick_origin(p3->facing, p7->facing), "moving <3>\n"));
	assert(!strcmp(find_kick_origin(p3->facing, p8->facing), "moving <1>\n"));

	assert(!strcmp(kick(p3->id, NULL), "ok\n"));
	assert(!strcmp(kick(p3->id, NULL), "ko\n"));

	assert(!strcmp(find_kick_origin(p4->facing, p5->facing), "moving <5>\n"));
	assert(!strcmp(find_kick_origin(p4->facing, p6->facing), "moving <3>\n"));
	assert(!strcmp(find_kick_origin(p4->facing, p7->facing), "moving <1>\n"));
	assert(!strcmp(find_kick_origin(p4->facing, p8->facing), "moving <7>\n"));
	
	assert(!strcmp(kick(p4->id, NULL), "ok\n"));
	assert(!strcmp(kick(p4->id, NULL), "ko\n"));
	


	printf("%s: ok\n", __func__);

}
