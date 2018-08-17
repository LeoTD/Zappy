#include "server.h"
#include "player_type.h"

/*
**	Display all resources and players in formatted display.
**	Grab current player, get the current tile of player and list all players and resources
**	except the current player itself.
**	Grab the NW tile and move right according to the current level counter.
*/

char	*find_next_tile_result(t_tile *tile)
{
	/* int		count; */
	/* char	*obj; */

	/* obj = strjoin_free(obj, find_food(tile)); */
	/* obj = strjoin_free(obj, find_stones(tile)); */
	/* obj = strjoin_free(obj, find_players(tile)); */
	/* return (obj); */

	// Find amount of food and store into string.
	// Find amount of each individual stone and strjoin_free to str.
	// Find amount of players on each tile and strjoin_free to str.
	// return str. 
	return (NULL);

}

char	*get_format_string(t_player *player, t_tile *tile)
{
	int		amount_per_row;
	int		vision_distance;
	char	*resulting_string;
	char	*next_tile_result;
	t_tile	*temp;

	vision_distance = 0;
	while (vision_distance <= player->level)
	{
		temp = tile;
		amount_per_row = 0;
		while (amount_per_row <= vision_distance * 2)
		{
			next_tile_result = find_next_tile_result(temp);
			resulting_string = "placeholder to make this compile";
			//resulting_string = ft_strjoin_free(resulting_string, next_tile_result);

			temp = get_adj_tile(temp, EAST);
		}
		vision_distance++;
		tile = get_adj_tile(tile, NORTHWEST);
	}
	return (resulting_string);
}

char	*see_tiles(int pid)
{
	char		*str;
	t_player	*player;

	player = get_player(pid);
	str = get_format_string(player, player->tile);
	return (str);
}
