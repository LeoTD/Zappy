#include "server.h"

#define MAX_OBJ_NAME_LENGTH 10
#define MAX_BROADCAST_LENGTH 4096

int			schd_add_cmd(int player_id, t_cmdfunc cmd,
		void *args, int delay_cycles)
{
	printf("\tplayer %d: cmd %p, args: %s; delay: %d\n", player_id,
			cmd, args, delay_cycles);
	return (0);
}

t_cmdfunc	string_to_command_fn_nullary(char *s)
{
	if (!strcmp("advance", s))
		return (advance);
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

t_cmdfunc	string_to_command_fn_unary(char *s, char **arg)
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
	*arg = malloc(len);
	strcpy(*arg, space + 1);
	if (*s == 'b')
		return (broadcast);
	if (*s == 'p')
		return (put);
	if (*s == 't')
		return (take);
	return (NULL);
}

int			get_cmd_tick_delay(t_cmdfunc f)
{
	if (f == connect_nbr)
		return (0);
	if (f == inventory)
		return (1);
	if (f == fork_player)
		return (42);
	if (f == incantation)
		return (300);
	return (7);
}

/*
** Note: Allocates an arg -- should be freed elsewhere after execution.
*/

int			enqueue_received_commands(char *msg, int player_id)
{
	t_cmdfunc		cmdfunc;
	void			*arg;
	int				delay;
	char			*nl;

	while ((nl = strchr(msg, '\n')))
	{
		arg = NULL;
		*nl = '\0';
		if (*msg == 't' || *msg == 'p' || *msg == 'b')
			cmdfunc = string_to_command_fn_unary(msg, (char **)&arg);
		else
			cmdfunc = string_to_command_fn_nullary(msg);
		if (cmdfunc)
		{
			delay = get_cmd_tick_delay(cmdfunc);
			if (schd_add_cmd(player_id, cmdfunc, arg, delay) == -1)
				break ;
		}
		msg = nl + 1;
	}
	return (0);
}
