#include "server.h"
#include "player_type.h"
#include "tile_type.h"

char	*existing_food_count(t_tile *tile)
{
	int		i;
	char	*str;

	str = strnew("");
	if (tile->count[FOOD] == 0)
		return (str);
	i = 0;
	while (i < tile->count[FOOD])
	{
		str = strjoin_free(strnew(" food"), str);
		i++;
	}
	return (str);
}

char	*existing_player_count(t_tile *tile)
{
	int		i;
	char	*str;

	str = strnew("");
	i = 0;
	while (i < tile->count[PLAYERS])
	{
		str = strjoin_free(strnew(" player"), str);
		i++;
	}
	return (str);
}

char	*add_existing_stone(t_tile *tile, int n)
{
	int		i;
	char	*count;

	if (tile->count[n] == 0)
		return (strnew(""));
	i = 0;
	count = strnew("");
	while (i < tile->count[n])
	{
		if (n == 0)
			count = strjoin_free(strnew(" linemate"), count);
		else if (n == 1)
			count = strjoin_free(strnew(" deraumere"), count);
		else if (n == 2)
			count = strjoin_free(strnew(" sibur"), count);
		else if (n == 3)
			count = strjoin_free(strnew(" mendiane"), count);
		else if (n == 4)
			count = strjoin_free(strnew(" phiras"), count);
		else if (n == 5)
			count = strjoin_free(strnew(" thystame"), count);
		i++;
	}
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
		if (tile->count[i] > 0)
		{
			temp = add_existing_stone(tile, i);
			str = strjoin_free(str, temp);
		}
		i++;
	}
	return (str);
}

