#ifndef COMMAND_LIST_TYPE_H
# define COMMAND_LIST_TYPE_H
# include "server.h"

t_command_list		*new_cmdlist(t_command *cmd);
void				free_cmdlist(t_command_list *list);

#endif
