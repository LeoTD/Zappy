#ifndef COMMAND_LIST_TYPE_H
# define COMMAND_LIST_TYPE_H
# include "server.h"

struct	s_command_list
{
	t_command				*cmd;
	struct s_command_list	*next;
};

#endif
