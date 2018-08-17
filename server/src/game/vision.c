#include "server.h"
#include "tile_type.h"
#include "player_type.h"

char	*add_next_tile(char *format, t_tile *temp)
{
	format = delimit(format, " ", existing_food_count(temp);
	format = delimit(format, " ", existing_stone_count(temp);
	format = delimit(format, " ", existing_player_count(temp);
	return (format);
}

char	*get_format_string(t_player *player, t_tile *tile)
{
	char	*format;
	t_tile	*temp;
	int		forward;
	int		right;

	forward = player_forward(player);
	right = player_right(player);
	vision_distance = 0;
	while (vision_distance <= player->level)
	{
		temp = tile;
		amount_per_row = 0;
		while (amount_per_row <= vision_distance * 2)
		{
			format = add_next_tile(format, temp);
			temp = get_adj_tile(temp, right);
			amount_per_row++;
		}
		tile = get_adj_tile(tile, NORTHWEST);
		vision_distance++;
	}
	return (format);
}

char	*see_tiles(int pid)
{
	char		*str;
	t_player	*player;
	
	player = get_player(pid);
	str = get_format_string(player, player->tile);
	return (str);
}
