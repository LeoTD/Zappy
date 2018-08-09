#include "server.h"

static t_plr_cmds	*g_plr_cmds = NULL;

int				schd_add_plr(int player_id)
{
	t_plr_cmds	*new;
	t_plr_cmds	*tmp;

	if (!(new = (t_plr_cmds*)ft_memalloc(sizeof(t_plr_cmds))))
		ERR_OUT("t_plr_cmd malloc failed\n");
	new->next_plr = NULL;
	new->cmd_list = NULL;
	new->player_id = player_id;
	new->cmd_count = 0;
	if (g_plr_cmds)
	{
		tmp = g_plr_cmds;
		while (tmp->next_plr)
			tmp = tmp->next_plr;
		tmp->next_plr = new;
	}
	else
		g_plr_cmds = new;
	return (0);
}

static t_cmd	*new_command(int player_id, t_command cmd,
						void *args, int delay_cycles)
{
	t_cmd	*new_cmd;

	if (!(new_cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd))))
		ERR_OUT("t_cmd malloc failed\n");
	new_cmd->next = NULL;
	new_cmd->player_id = player_id;
	new_cmd->cmd = cmd;
	new_cmd->args = args;
	new_cmd->timestamp = 0;		//Determine timestamping!
	new_cmd->delay_cycles = delay_cycles;

	return (new_cmd);
}

/*
** Locates corresponding player and appends command to queue.
**	Returns -1 if player command queue is full.
**	exits if player_id not found.
*/

int				schd_add_cmd(int player_id, t_command cmd,
						void *args, int delay_cycles)
{
	t_plr_cmds	*node;
	t_cmd		*new_cmd;
	t_cmd		*last_cmd;

	node = g_plr_cmds;
	while (node->player_id != player_id)
		node = node->next_plr;
	assert(node);
	if (node->cmd_count >= 10)
		return (-1);
	new_cmd = new_command(player_id, cmd, args, delay_cycles);
	if (node->cmd_list)
	{
		last_cmd = node->cmd_list;
		while (last_cmd->next)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
	}
	else
		node->cmd_list = new_cmd;
	node->cmd_count++;
	return (0);
}

/*
** Pops leading command to executioner, decrements players cmd_count, and
** points players leading command to next in cmd_list
*/

static int				pop_command(t_plr_cmds *plr)
{
	if (plr)
		return (1);
	return (0);
}

/*
** Main scheduler function. runs through player list and decrements leading
** command's delay_cycles. If delay_cylces == 0, pop command onto executioner,
** move player cmd_list pointer over to new lead and decrement cmd_count.
*/

int						schd_step_cycle(void)
{
	t_plr_cmds	*plr;

	plr = g_plr_cmds;
	while (plr)
	{
		if (plr->cmd_list)
		{
			if (CMD_COUNTDOWN(plr) == 0)
				pop_command(plr);
			else
				CMD_COUNTDOWN(plr)--;
		}
		plr = plr->next_plr;
	}
	return (0);
}
