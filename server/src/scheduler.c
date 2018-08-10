#include "server.h"

<<<<<<< HEAD
static t_cmd_queue	*g_cmd_queue = NULL;

int					schd_add_plr(int player_id)
{
	t_cmd_queue	*new;
	t_cmd_queue	*tmp;

	if (!(new = (t_cmd_queue*)ft_memalloc(sizeof(t_cmd_queue))))
=======
static t_plr_cmds	*g_plr_cmds = NULL;

int				schd_add_plr(int player_id)
{
	t_plr_cmds	*new;
	t_plr_cmds	*tmp;

	if (!(new = (t_plr_cmds*)ft_memalloc(sizeof(t_plr_cmds))))
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
		ERR_OUT("t_plr_cmd malloc failed\n");
	new->next_plr = NULL;
	new->cmd_list = NULL;
	new->player_id = player_id;
	new->cmd_count = 0;
<<<<<<< HEAD
	if (g_cmd_queue)
	{
		tmp = g_cmd_queue;
=======
	if (g_plr_cmds)
	{
		tmp = g_plr_cmds;
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
		while (tmp->next_plr)
			tmp = tmp->next_plr;
		tmp->next_plr = new;
	}
	else
<<<<<<< HEAD
		g_cmd_queue = new;
	return (0);
}

static t_cmd		*new_command(int player_id, t_cmd_func cmd,
=======
		g_plr_cmds = new;
	return (0);
}

static t_cmd	*new_command(int player_id, t_cmdfunc cmd,
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
						void *args, int delay_cycles)
{
	t_cmd	*new_cmd;

	if (!(new_cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd))))
		ERR_OUT("t_cmd malloc failed\n");
	new_cmd->next = NULL;
	new_cmd->player_id = player_id;
<<<<<<< HEAD
	new_cmd->do_cmd = cmd;
=======
	new_cmd->cmd = cmd;
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
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

<<<<<<< HEAD
int					schd_add_cmd(int player_id, t_cmd_func cmd,
						void *args, int delay_cycles)
{
	t_cmd_queue	*node;
	t_cmd		*new_cmd;
	t_cmd		*last_cmd;

	node = g_cmd_queue;
=======
int				schd_add_cmd(int player_id, t_cmdfunc cmd,
						void *args, int delay_cycles)
{
	t_plr_cmds	*node;
	t_cmd		*new_cmd;
	t_cmd		*last_cmd;

	node = g_plr_cmds;
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
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
<<<<<<< HEAD
			NEXT_CMD(last_cmd);
=======
			last_cmd = last_cmd->next;
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
		last_cmd->next = new_cmd;
	}
	else
		node->cmd_list = new_cmd;
	node->cmd_count++;
	return (0);
}

/*
<<<<<<< HEAD
** Kills coresponding player when they run out of food.
** Removes coresponding t_cmd_queue from g_cmd_queue list.
*/

int					schd_kill_plr(int player_id)
{
	t_cmd_queue		*this_cmd_queue;
	t_cmd_queue		*prev_cmd_queue;

	this_cmd_queue = g_cmd_queue;
	if (g_cmd_queue->player_id == player_id)
		g_cmd_queue = g_cmd_queue->next_plr;
	else
	{
		while (this_cmd_queue && this_cmd_queue->player_id != player_id)
		{
			prev_cmd_queue = this_cmd_queue;
			this_cmd_queue = this_cmd_queue->next_plr;
		}
		assert(this_cmd_queue);
		prev_cmd_queue->next_plr = this_cmd_queue->next_plr;
	}
	exec_free_cmds(this_cmd_queue->cmd_list);
	free(this_cmd_queue);
	return (0);
}

/*
** Pops leading command to ready_cmds, decrements players cmd_count, and
** points players leading command to next in cmd_list
*/

static int			pop_command(t_cmd_queue *plr, t_cmd *list)
{
	t_cmd	*popped_cmd;

	popped_cmd = plr->cmd_list;
	if (list)
	{
		while (list->next)
			NEXT_CMD(list);
		list->next = popped_cmd;
	}
	else
		list = popped_cmd;
	plr->cmd_list = plr->cmd_list->next;
	popped_cmd->next = NULL;
	plr->cmd_count--;
=======
** Pops leading command to executioner, decrements players cmd_count, and
** points players leading command to next in cmd_list
*/

static int				pop_command(t_plr_cmds *plr)
{
	if (plr)
		return (1);
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
	return (0);
}

/*
** Main scheduler function. runs through player list and decrements leading
<<<<<<< HEAD
** command's delay_cycles. If delay_cylces == 0, pop command onto return,
** move player cmd_list pointer over to new lead.
*/

int					schd_step_cycle(t_cmd **lit_cmds)
{
	t_cmd_queue		*plr;
	t_cmd			*ready_cmds;

	ready_cmds = NULL;
	plr = g_cmd_queue;
=======
** command's delay_cycles. If delay_cylces == 0, pop command onto executioner,
** move player cmd_list pointer over to new lead and decrement cmd_count.
*/

int						schd_step_cycle(void)
{
	t_plr_cmds	*plr;

	plr = g_plr_cmds;
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
	while (plr)
	{
		if (plr->cmd_list)
		{
<<<<<<< HEAD
			if (CMD_READY(plr))
				while (CMD_READY(plr))
					pop_command(plr, ready_cmds);
=======
			if (CMD_COUNTDOWN(plr) == 0)
				pop_command(plr);
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
			else
				CMD_COUNTDOWN(plr)--;
		}
		plr = plr->next_plr;
	}
<<<<<<< HEAD
	*lit_cmds = ready_cmds;
=======
>>>>>>> 290b500ee05795024097585684e4d21ddd2511b7
	return (0);
}
