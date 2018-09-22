#include "server.h"
#include "player_type.h"
#include "command_queue_type.h"
#include "command_type.h"
#include "client_type.h"
#include "tile_type.h"
#include "fork_player.h"

struct s_hatch_args	*create_hatch_args(t_player *p)
{
	struct s_hatch_args	*a;

	a = malloc(sizeof(*a));
	a->x = p->tile->x;
	a->y = p->tile->y;
	a->team_id = p->team_id;
	return (a);
}

char				*fork_finish(int player_id, void *args)
{
	struct s_hatch_args	*a;
	t_player			*p;

	(void)player_id;
	a = args;
	p = new_player(a->team_id);
	add_player_to_tile(p, &g_map->tile[a->x][a->y]);
	p->tile->eggs -= 1;
	gfx_sendall("EGG_HATCH %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		p->id, p->team_id, p->level, p->tile->x, p->tile->y, p->energy,
		p->facing, p->count[FOOD],
		p->count[LINEMATE], p->count[DERAUMERE], p->count[SIBUR],
		p->count[MENDIANE], p->count[PHIRAS], p->count[THYSTAME]);
	free(a);
	return (NULL);
}

char				*fork_player(int player_id, void *args)
{
	t_command		*hatch_event;
	t_command_queue	*hatch_queue;
	t_player		*p;

	(void)args;
	hatch_event = new_cmd(fork_finish);
	p = get_player(player_id);
	hatch_event->args = create_hatch_args(p);
	hatch_queue = get_hatch_queue();
	if (hatch_queue->remaining_space < MAX_COMMANDS)
		hatch_queue->remaining_space += 1;
	hatch_event->player_id = get_cmdfunc_tick_delay(fork_finish);
	enqueue_command(hatch_queue, hatch_event);
	p->tile->eggs += 1;
	gfx_sendall("DONE_LAYING_EGG %d %d %d %d\n",
			p->id, p->team_id, p->tile->x, p->tile->y);
	return ("ok\n");
}
