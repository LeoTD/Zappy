#include "server.h"

int					get_cmdfunc_tick_delay(t_cmdfunc f)
{
	if (f == connect_nbr)
		return (0);
	if (f == inventory)
		return (1);
	if (f == fork_player)
		return (42);
	if (f == incantation)
		return (0);
	if (f == incantation_finish)
		return (300);
	if (f == fork_finish)
		return (600);
	return (7);
}

static t_cmdfunc	string_to_cmdfunc_nullary(char *s)
{
	if (!strcmp("advance", s))
		return (advance);
	if (!strcmp("connect_nbr", s))
		return (connect_nbr);
	if (!strcmp("fork", s))
		return (fork_player);
	if (!strcmp("incantation", s))
		return (incantation);
	if (!strcmp("inventory", s))
		return (inventory);
	if (!strcmp("kick", s))
		return (kick);
	if (!strcmp("left", s))
		return (left);
	if (!strcmp("right", s))
		return (right);
	if (!strcmp("see", s))
		return (see);
	return (NULL);
}

static t_cmdfunc	string_to_cmdfunc_unary(char *s, char **arg_ptr)
{
	size_t		len;
	size_t		max_len;
	char		*space;

	if (!(space = strchr(s, ' ')))
		return (NULL);
	*space = '\0';
	if (strcmp("broadcast", s) && strcmp("put", s) && strcmp("take", s))
		return (NULL);
	max_len = *s == 'b' ? MAX_BROADCAST_LENGTH : MAX_OBJ_NAME_LENGTH;
	len = strnlen(space + 1, max_len);
	if ((space + 1)[len] != '\0')
		return (NULL);
	asprintf(arg_ptr, "%s", space + 1);
	if (*s == 'b')
		return (broadcast);
	if (*s == 'p')
		return (put);
	if (*s == 't')
		return (take);
	return (NULL);
}

t_cmdfunc			string_to_cmdfunc(char *string, char **arg_ptr)
{
	if (*string == 't' || *string == 'p' || *string == 'b')
		return (string_to_cmdfunc_unary(string, arg_ptr));
	return (string_to_cmdfunc_nullary(string));
}
