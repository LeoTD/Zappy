#include "server.h"
#include "player_type.h"

/*
**	Example end string: {food 356, linemate 2, draumere 3, sibur 4, mendiane 5, ...}
**	
*/

char	*wrap(char *str)
{
	str = strjoin_free(strnew("{"), str);
	str = strjoin_free(str, strnew("}"));
	return (str);
}

char	*delimit(char *str1, char *d, char *str2)
{
	str1 = realloc(str1, strlen(str1) + strlen(str2) + strlen(d) + 1);
	str1 = strcpy(str1, d);
	str1 = strcpy(str1, str2);
	bzero(str2, strlen(str2));
	free(str2);
	return (str1);
}

char	*search_inventory(t_player *player)
{
	char	*all;
	char	*food_and_count;
	char	*stones_and_count;

	food_and_count = find_food(player);
	stones_and_count = find_stones(player);
	all = strjoin_free(food_and_count, stones_and_count);
	all = wrap(all);
	return (all);
}

char	*get_player_inventory(int pid)
{
	char		*inventory;
	t_player	*player;

	player = get_player(pid);
	inventory = search_inventory(player);
	return (inventory);
}

