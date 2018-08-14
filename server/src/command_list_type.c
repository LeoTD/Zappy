#include "command_list_type.c"

t_command_list		*new_cmdlist(t_command *cmd)
{
	t_command_list	*holder;

	if(!(holder = malloc(sizeof(t_command_list))))
		return (NULL);
	holder->cmd = cmd;
	holder->next = NULL;
	return (holder);
}

/*
** might change it to a double pointer
*/
void						free_cmdlist(t_command_list *list)
{
	t_command_list	*iter;
	t_command_list	*purger;

	purger = NULL;
	iter = NULL;
	if (!(list))
		return;
	iter = list->next;
	while(iter)
	{
		purger = iter;
		iter = iter->next;
		free(purger);
	}
	free(list);
}
