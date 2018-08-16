#include "server.h"
#include "tile_type.h"

#define OK_COLOR "\033[1;35m"

int			test_player_creation(void)
{
	t_player	*p;
	t_tile		*t;

	create_map(10, 10);
	place_random_stones(0, 30);
	place_random_stones(1, 30);
	place_random_stones(2, 30);
	place_random_stones(3, 30);
	place_random_stones(4, 30);
	place_random_stones(5, 30);
	place_random_food(30);
	t = &g_map->tile[0][0];
	for(int i = 0; i < 4000; i++)
	{
		p = new_player(0, 1);
		add_player_to_tile(p, t);
	//	printf("pid = %d\n", p->id);
	}
//	printf("Standing on: (%d, %d)\n", p->tile->x, p->tile->y);
	assert(is_player_on_tile(p, t) == p);
	printf("%s[ OK ]                                    \033[0mPlayer's created and placed!\n", OK_COLOR);
	return (0);
}
