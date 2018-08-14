#ifndef COMMAND_LIST_TYPE_H
# define COMMAND_LIST_TYPE_H
# include "server.h"
# define MAX_COMMANDS	10

typedef struct				s_command_list
{
	struct	s_command		*cmd;
	struct	s_command_list	*next;
}							t_command_list;

t_command_list				*new_cmdlist(t_command *cmd);
void						free_cmdlist(t_command_list *list);

#endif
