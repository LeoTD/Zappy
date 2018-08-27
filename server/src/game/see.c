#include "server.h"
#include "tile_type.h"
#include "player_type.h"

char	*add_next_tile(char *format, t_tile *temp, int pid)
{
	format = strjoin_free(format, strnew(","));
	format = strjoin_free(format, existing_player_count(temp, pid));
	format = strjoin_free(format, existing_food_count(temp));
	format = strjoin_free(format, existing_stone_count(temp));
	return (format);
}

char	*first_tile(char *format, t_tile *temp, int pid)
{
	format = strjoin_free(format, existing_player_count(temp, pid));
	format = strjoin_free(format, existing_food_count(temp));
	format = strjoin_free(format, existing_stone_count(temp));
	return (format);
}

char	*get_format_string(t_player *player, t_tile *tile)
{
	char	*format;
	t_tile	*temp;
	int		forward;
	int		right;
	int		vision_distance;
	int		amount_per_row;
	int		first;

	first = 0;
	forward = player_forward(player);
	right = player_right(player);
	vision_distance = 0;
	format = first_tile(strnew(""), tile, player->id);
	while (vision_distance < player->level)
	{
		temp = tile;
		amount_per_row = 0;
		while (amount_per_row <= vision_distance * 2)
		{
			format = add_next_tile(format, temp, player->id);
			temp = get_adj_tile(temp, right);
			amount_per_row++;
		}
		tile = get_adj_tile(tile, NORTHWEST);
		vision_distance++;
	}
	format = wrap("{", format, " }\n");
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
