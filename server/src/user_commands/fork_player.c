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
	free(a);
	return (NULL);
}

char				*fork_player(int player_id, void *args)
{
	t_command		*hatch_event;
	t_command_queue	*hatch_queue;

	(void)args;
	hatch_event = new_cmd(fork_finish);
	hatch_event->args = (char *)create_hatch_args(get_player(player_id)); // FIXME make commands "events", make args void *
	hatch_queue = get_hatch_queue();
	if (hatch_queue->remaining_space < MAX_COMMANDS)
		hatch_queue->remaining_space += 1;
	/*
	 * Ugly hack. Command queues have timers, but individual commands within
	 * them don't, at the moment. This is fine for user commands, since only the
	 * event at the head of the queue is supposed to tick down anyway; but it's a problem
	 * for hatch events -- if 10 eggs are laid on the same tick, they should all hatch
	 * at the same time. Treated as a normal command, egg #2 would hatch 600 ticks after #1.
	 *
	 * The correct solution is to go back and rewrite everything
	 * to be less user-command specific: 'events' instead of 'commands' all the way
	 * through, with an event implemented as a node in a doubly-linked list.
	 * But for now, we use player_id as a fake timer, one per egg.
	 * The check_and_hatch_eggs function just checks that, ignoring
	 * its own dequeue_timer.
	 */
	hatch_event->player_id = get_cmdfunc_tick_delay(fork_finish);
	enqueue_command(hatch_queue, hatch_event);
	return ("ok\n");
}
