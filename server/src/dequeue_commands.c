#include "server.h"
#include "command_type.h"
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
		popped_tail->next = cmd_queue->head;
		cmd_queue->head = cmd_queue->head->next;
		popped_tail->next->next = NULL;
	}
	else
	{
		*popped_head = cmd_queue->head;
		cmd_queue->head = cmd_queue->head->next;
		(*popped_head)->next = NULL;
	}
}

static void		step_client_queue(t_client *client)
{
	client->cmdqueue->remaining_space++;
	if (client->cmdqueue->head)
		client->cmdqueue->dequeue_timer = get_cmdfunc_tick_delay(client->cmdqueue->head->cmd->cmdfunc);
	else
		client->cmdqueue->dequeue_timer = -1;
}

t_command_list	*dequeue_commands(t_client **user_clients, int player_count)
{
	t_command_list	*popped_cmds;
	int				i;

	popped_cmds = NULL;
	i = -1;
	while (++i < player_count)
	{
		if (user_clients[i]->cmdqueue->dequeue_timer == 0)
		{
			assert(user_clients[i]->cmdqueue->head);
			pop_command(&popped_cmds, user_clients[i]->cmdqueue);
			step_client_queue(user_clients[i]);
		}
	}
    return (popped_cmds);
}
