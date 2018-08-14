#ifndef COMMAND_TYPE_H
# define COMMAND_TYPE_H
# include "server.h"

t_command		*new_cmd(t_cmdfunc f, int player_id);
void			free_cmd(t_command *cmd);

#endif
