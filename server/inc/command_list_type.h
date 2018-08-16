#ifndef COMMAND_LIST_TYPE_H
# include "command_type.h"
# define COMMAND_LIST_TYPE_H

struct s_command_list
{
	t_command		*cmd;
	struct s_command_list	*next;
};
#endif
