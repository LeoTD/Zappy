#include "server.h"

static void	accept_clients_and_new_messages(void)
{
	int	fd;

	while ((fd = get_readable_socket()) != -1)
	{
		if (is_connection_type(fd, SERVER))
			initiate_handshake(fd);
		else if (is_connection_type(fd, HANDSHAKE))
			continue_handshake(fd);
		else
		{
			assert(is_connection_type(fd, USER));
			receive_user_message(fd);
		}
	}
}

int	main(int argc, char **argv)
{
	t_command_list	*cmds;
	int				winning_team_id;

	parse_command_line_options(argc, argv);
	listen_for_connections(g_opts.server_port);
	while (1)
	{
		accept_clients_and_new_messages();
		if (have_we_ticked())
		{
			remove_dead_players();
			cmds = dequeue_commands();
			execute_command_list(cmds);
			if (is_game_over(&winning_team_id))
				handle_game_over(winning_team_id);
			send_results_to_users(cmds);
			free_cmdlist(cmds);
			decrement_user_command_timers();
		}
	}
	return (0);
}
