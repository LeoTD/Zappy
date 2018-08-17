#include "server.h"
#include "player_type.h"
#include "tile_type.h"

char	*existing_food_count(t_tile *tile)
{
	char	*str;

	if (tile->food > 0)
	{
		str = strnew("food ");
		str = strjoin_free(str, itoa(tile->food));
		return (str);
	}
	return (strnew(""));
}

char	*existing_player_count(t_tile *tile)
{
	char	*str;

	if (tile->num_players > 1)
	{
		str = strnew("players ");
		str = strjoin_free(str, itoa(tile->num_players - 1));
		return (str);
	}
	return (strnew(""));
}

char	*add_existing_stone(t_tile *tile, int n)
{
	char	*count;

	count = itoa(tile->stones[n]);
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

char	*existing_stone_count(t_tile *tile)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	str = strnew("");
	while (i < 6)
	{
		if (tile->stones[i] > 0)
		{
			temp = add_existing_stone(tile, i);
			str = strjoin_free(str, temp);
		}
		i++;
	}
	return (str);
}

