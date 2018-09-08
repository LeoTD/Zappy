#include "server.h"
#include "player_type.h"

char	*find_food(t_player *player)
{
	char	*count;

	count = itoa(player->count[FOOD] * 126 + player->energy);
	count = strjoin_free(strnew("food "), count);
	return (count);
}

char	*add_stone(t_player *player, int n)
{
	char	*count;

	count = itoa(player->count[n]);
	if (n == 0)
		count = strjoin_free(strnew(", linemate "), count);
	else if (n == 1)
		count = strjoin_free(strnew(", deraumere "), count);
	else if (n == 2)
		count = strjoin_free(strnew(", sibur "), count);
	else if (n == 3)
		count = strjoin_free(strnew(", mendiane "), count);
	else if (n == 4)
		count = strjoin_free(strnew(", phiras "), count);
	else if (n == 5)
		count = strjoin_free(strnew(", thystame "), count);	
	return (count);
}

char	*find_stones(t_player *player)
{
	int		i;
	char	*stone_array;

	i = 0;
	stone_array = strnew("");
	while (i < 6)
	{
		stone_array = strjoin_free(stone_array, add_stone(player, i));
		i++;
	}
	return (stone_array);
}
