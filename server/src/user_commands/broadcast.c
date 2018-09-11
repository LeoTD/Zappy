#include "server.h"
#include "player_type.h"
#include "tile_type.h"
#include "client_type.h"

static char	g_broadcast_buf[MAX_BROADCAST_LENGTH + 10 + 2]; // 10 = starting "message K ", 2 = ending "\n\0"
static size_t g_broadcast_len;

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

int		get_message_transmission_direction(int sourcex, int sourcey,
											int destx, int desty)
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
	int			direction;
	t_client	**clients;
	t_player	*sender;
	t_player	*p;

	clients = get_clients();
	snprintf(g_broadcast_buf, MAX_BROADCAST_LENGTH, "message K %s\n", args);
	g_broadcast_len = strlen(g_broadcast_buf);
	sender = get_player(player_id);
	while (clients[0])
	{
		p = get_player(clients[0]->player_id);
		direction = get_message_transmission_direction(
				sender->tile->x, sender->tile->y, p->tile->x, p->tile->y);
		if (direction > 0)
			direction = perceived_direction(direction, p);
		g_broadcast_buf[8] = direction + '0';
		send(clients[0]->socket_fd, g_broadcast_buf, g_broadcast_len, 0);
		++clients;
	}
	return ("ok\n");
}
