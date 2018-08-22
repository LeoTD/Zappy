#include "server.h"
#include "command_list_type.h"
#include "command_queue_type.h"
#include "client_type.h"

static void		pop_command(t_command_list **popped_head, t_command_queue *cmd_queue)
{
	t_command_list	*popped_tail;

	if (*popped_head)
	{
		popped_tail = *popped_head;
		while (popped_tail->next)
			popped_tail = popped_tail->next;
		popped_tail->next = dequeue_command(cmd_queue);
	}
	else
	{
		*popped_head = dequeue_command(cmd_queue);
	}
}

static void print_client_queues(t_client **clients) {
	for (int i = 0; clients[i]; i++) {
		t_command_queue *q = clients[i]->cmdqueue;
		printf("p%d->(timer: %d, rem_space: %d)%s",
				clients[i]->player_id,
				q->dequeue_timer,
				q->remaining_space,
				clients[i + 1] ? ", " : "]\n");
	}
}

t_command_list	*dequeue_commands(t_client **user_clients)
{
	t_command_list	*popped_cmds;
	int				i;

	print_client_queues(user_clients);
	popped_cmds = NULL;
	i = -1;
	while (user_clients[++i])
	{
		while (user_clients[i]->cmdqueue->dequeue_timer == 0)
		{
			assert(user_clients[i]->cmdqueue->head);
			pop_command(&popped_cmds, user_clients[i]->cmdqueue);
		}
	}
    return (popped_cmds);
}
