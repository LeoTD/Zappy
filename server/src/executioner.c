#include "server.h"

#define DO_CMD_FUNC(cmd)	(cmd->do_cmd(cmd->player_id, cmd->args))
#define NEXT_CMD(cmd)		(cmd = cmd->next)

int         exec_utioner(t_cmd *cmd_exec_list)
{
    t_cmd		*current_cmd;

	if (!cmd_exec_list)
		return (0);			//maybe -1?
	current_cmd = cmd_exec_list;
	while (current_cmd)
	{
		DO_CMD_FUNC(current_cmd);
		NEXT_CMD(current_cmd);
	}
	exec_free_cmds(cmd_exec_list);
    return (0);
}

void		exec_free_cmds(t_cmd *list)
{
	if (!list)
		return ;
	if (list->next)
		exec_free_cmds(list->next);
	free(list);
}
