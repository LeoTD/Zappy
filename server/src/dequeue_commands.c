#include "server.h"
#include "command_list_type.h"
#include "command_queue_type.h"
#include "client_type.h"
#include "player_type.h"

static void		ply_pop_command(t_command_list **popped_head,
		t_ply_cmd_queue *cmd_queue)
{
	t_command_list	*popped_tail;

	if (*popped_head)
	{
		popped_tail = *popped_head;
		while (popped_tail->next)
			popped_tail = popped_tail->next;
		popped_tail->next = ply_dequeue_command(cmd_queue);
	}
	else
	{
		*popped_head = ply_dequeue_command(cmd_queue);
	}
}

t_command_list	*dequeue_commands(t_client **user_clients)
{
	t_command_list	*popped_cmds;
	int				i;

	popped_cmds = NULL;
	i = -1;
	while (user_clients[++i])
	{
		if (user_clients[i]->type == ACTIVE_PLAYER)
		{
			while (user_clients[i]->cmdqueue.dequeue_timer == 0)
			{
				ply_pop_command(&popped_cmds, &(user_clients[i]->cmdqueue));
			}
		}
	}
	return (popped_cmds);
}
