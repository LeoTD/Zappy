#include "server.h"
#include "player_type.h"
#include "tile_type.h"
#include "client_type.h"

int		distance_along_wrapped_dimension(int p1, int p2, int dim)
{
	int	d;
	d = p2 - p1;
	if (abs(d) > dim / 2)
	{
		d = dim - abs(d);
		if (p2 > p1)
			d *= -1;
	}
	return (d);
}

int		*point_to_greater_abs_value(int *a, int *b)
{
	if (abs(*a) == abs(*b))
		return (NULL);
	else if (abs(*a) > abs(*b))
		return (a);
	else
		return (b);
}

int		perceived_direction(enum e_directions d, t_player *p)
{
	return ((d - p->facing + NUM_DIRECTIONS) % NUM_DIRECTIONS + MIN_DIRECTION);
}

int		get_message_transmission_direction(int sourcex, int sourcey, int destx, int desty)
{
	int	dx;
	int	dy;
	int *larger_delta;

	dx = distance_along_wrapped_dimension(sourcex, destx, g_opts.world_width);
	dy = distance_along_wrapped_dimension(sourcey, desty, g_opts.world_height);
	larger_delta = point_to_greater_abs_value(&dx, &dy);
	if (dx == 0 && dy == 0)
		return (0);
	if (larger_delta == &dy && dy > 0)
		return (1);
	if (larger_delta == NULL && dx > 0 && dy > 0)
		return (2);
	if (larger_delta == &dx && dx > 0)
		return (3);
	if (larger_delta == NULL && dx > 0 && dy < 0)
		return (4);
	if (larger_delta == &dy && dy < 0)
		return (5);
	if (larger_delta == NULL && dx < 0 && dy < 0)
		return (6);
	if (larger_delta == &dx && dx < 0)
		return (7);
	return (8);
}

char	*broadcast(int player_id, void *args)
{
	static char	buf[MAX_BROADCAST_LENGTH + 10 + 2]; // 10 = starting "message K ", 2 = ending "\n\0"
	int			len;
	int			direction;
	t_client	**clients;
	t_player	*sender;

	clients = get_clients();
	snprintf(buf, MAX_BROADCAST_LENGTH, "message K %s\n", (char *)args);
	len = strlen(buf);
	sender = get_player(player_id);
	while (clients[0])
	{
		t_player *p = get_player(clients[0]->player_id);
		direction = get_message_transmission_direction(
				sender->tile->x, sender->tile->y, p->tile->x, p->tile->y);
		if (direction > 0)
			direction = perceived_direction(direction, p);
		buf[8] = direction + '0';
		send(clients[0]->socket_fd, buf, len, 0);
		++clients;
	}
	return ("ok\n");
}
