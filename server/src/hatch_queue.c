#include "server.h"
#include "command_list_type.h"
#include "command_queue_type.h"
#include "command_type.h"

static t_command_queue	*g_hatch_queue;

void			init_global_hatch_queue(void)
{
	g_hatch_queue = new_cmdqueue();
}

t_command_queue	*get_hatch_queue(void)
{
	return (g_hatch_queue);
}

t_command_list	*get_hatch_events_this_tick(void)
{
	t_command_list	*curr;
	t_command_list	*head;

	curr = NULL;
	head = NULL;
	while (g_hatch_queue->head && g_hatch_queue->head->cmd->player_id == 0)
	{
		if (!curr)
		{
			curr = dequeue_command(g_hatch_queue);
			head = curr;
		}
		else
			curr->next = dequeue_command(g_hatch_queue);
		curr = curr->next;
	}
	return (head);
}

void			decrement_hatch_event_timers(void)
{
	t_command_list	*event;

	event = g_hatch_queue->head;
	while (event)
	{
		assert(event->cmd);
		event->cmd->player_id -= 1;
		event = event->next;
	}
}

void			check_and_hatch_eggs(void)
{
	t_command_list	*hatch_events;

	hatch_events = get_hatch_events_this_tick();
	execute_command_list(hatch_events);
	decrement_hatch_event_timers();
	free_cmdlist(hatch_events);
}
