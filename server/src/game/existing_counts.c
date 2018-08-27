#include "server.h"
#include "player_type.h"
#include "tile_type.h"

char	*existing_food_count(t_tile *tile)
{
	int		i;
	char	*str;

	str = strnew("");
	if (tile->food == 0)
		return (str);
	i = 0;
	while (i < tile->food)
	{
		str = strjoin_free(strnew(" food"), str);
		i++;
	}
	return (str);
}

char	*existing_player_count(t_tile *tile, int pid)
{
	int		i;
	int		*players;
	int		size;
	char	*str;

	str = strnew("");
	if (tile->num_players == 0)
		return (str);
	players = get_current_tile_player_count(pid, &size);
	i = size - 1;
	while (i >= 0)
	{
		if (players[i] == pid)
			size--;
		i--;
	}
	i = 0;
	while (i < size)
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

	if (tile->stones[n] == 0)
		return (strnew(""));
	i = 0;
	count = strnew("");
	while (i < tile->stones[n])
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
		if (tile->stones[i] > 0)
		{
			temp = add_existing_stone(tile, i);
			str = strjoin_free(str, temp);
		}
		i++;
	}
	return (str);
}

