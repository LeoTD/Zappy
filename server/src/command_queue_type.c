#include "server.h"
#include "command_queue_type.h"
#include "command_list_type.h"
#include "command_type.h"

t_command_queue		*new_cmdqueue(void)
{
	t_command_queue		*holder;

	if (!(holder = malloc(sizeof(t_command_queue))))
		return (NULL);
	holder->head = NULL;
	holder->tail = NULL;
	holder->remaining_space = MAX_COMMANDS;
	holder->dequeue_timer = -1;
	return (holder);
}

int					enqueue_command(t_command_queue *q, t_command *cmd)
{
	if (!q || q->remaining_space <= 0)
		return (-1);
	else
	{
		if (!q->head)
		{
			q->head = new_cmdlist(cmd);
			q->tail = q->head;
			q->dequeue_timer = get_cmdfunc_tick_delay(q->head->cmd->cmdfunc);
		}
		else
		{
			q->tail->next = new_cmdlist(cmd);
			q->tail = q->tail->next;
		}
		q->remaining_space--;
		return (0);
	}
}

t_command_list		*dequeue_command(t_command_queue *q)
{
	t_command_list	*temp;

	temp = NULL;
	if (!q || !(q->head))
		return (NULL);
	else
	{
		if (q->head == q->tail)
			q->tail = NULL;
		temp = q->head;
		q->head = q->head->next;
		temp->next = NULL;
		if (q->head)
			q->dequeue_timer = get_cmdfunc_tick_delay(q->head->cmd->cmdfunc);
		else
			q->dequeue_timer = -1;
		q->remaining_space += 1;
		return (temp);
	}
}
