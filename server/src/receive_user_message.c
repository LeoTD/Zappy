#include "server.h"
#include "client_type.h"
#include "command_queue_type.h"
#include "command_type.h"

#define MAX_USER_COMMAND_LENGTH 4096
#define MAX_USER_CLIENT_RECV (MAX_USER_COMMAND_LENGTH * MAX_COMMANDS)

char		*read_user_buffer(int cli_fd)
{
	char	buf[MAX_USER_CLIENT_RECV + 1];
	int		count;
	char	*s;

	s = NULL;
	if ((count = recv(cli_fd, buf, MAX_USER_CLIENT_RECV, 0)) > 0)
	{
		buf[count] = '\0';
		s = malloc(count);
		strcpy(s, buf);
	}
	return (s);
}

t_command	*message_extract_next_command(char *msg, char **msg_next)
{
	char		*nl;
	t_command	*cmd;

	cmd = NULL;
	if (*msg && (nl = strchr(msg, '\n')))
	{
		*nl = '\0';
		cmd = string_to_command(msg);
		*nl = '\n';
		*msg_next = nl + 1;
	}
	else
		*msg_next = strchr(msg, '\0');
	return (cmd);
}

void		enqueue_commands_from_user_message(t_client *client, char *msg)
{
	char		*msg_next;
	t_command	*cmd;

	msg_next = msg;
	while (client->cmdqueue->remaining_space > 0 && *msg_next)
	{
		if ((cmd = message_extract_next_command(msg, &msg_next)))
		{
			cmd->player_id = client->player_id;
			enqueue_command(client->cmdqueue, cmd);
		}
		msg = msg_next;
	}
}

void	receive_user_message(int cli_fd)
{
	t_client	*client;
	char		*msg;

	client = get_client_by_socket_fd(cli_fd);
	if (!(msg = read_user_buffer(cli_fd)))
	{
		socket_lookup_remove(cli_fd);
		unregister_client_by_player_id(client->player_id);
		return ;
	}
	enqueue_commands_from_user_message(client, msg);
	free(msg);
}
