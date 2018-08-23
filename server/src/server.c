#include "server.h"

void	start_server_and_game(void)
{
	game_init(g_opts.world_width, g_opts.world_height,
			g_opts.teamcount, g_opts.initial_players_per_team);
	listen_for_connections(g_opts.server_port);
	init_tick_timer();
}

int		main(int argc, char **argv)
{
	t_command_list	*cmds;
	int				winning_team_id;
	int				fd;
	t_client		**user_clients;

	parse_command_line_options(argc, argv);
	start_server_and_game();
	while (1)
	{
		user_clients = get_clients();
		while ((fd = iter_next_readable_socket()) != -1)
			handle_waiting_connection_data(fd);
		if (have_we_ticked())
		{
			game_upkeep();
		//	remove_dead_players();
			cmds = dequeue_commands(user_clients);
			execute_command_list(cmds);
			if (is_game_over(&winning_team_id))
				handle_game_over(winning_team_id);
			send_stringified_responses(cmds);
			free_cmdlist(cmds);
			decrement_user_command_timers(user_clients);
		}
	}
	return (0);
}
