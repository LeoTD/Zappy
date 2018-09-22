#include "server.h"
#include "command_list_type.h"
#include "command_type.h"

void	execute_command_list(t_command_list *list)
{
	while (list)
	{
		list->cmd->response = list->cmd->cmdfunc(list->cmd->player_id,
				list->cmd->args);
		list = list->next;
	}
}
