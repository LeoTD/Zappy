#include "server.h"

#include "client_type.h" // XXX
#include "player_type.h" // XXX
#include "command_queue_type.h" // XXX
void			print_client_queues(t_client **clients)
{
	for (int i = 0; clients[i]; i++)
	{
		t_player *p = get_player(clients[i]->player_id);
		t_command_queue *q = clients[i]->cmdqueue;
		printf("p%d->(timer: %d, rem_space: %d, energy: %d)%s",
				clients[i]->player_id,
				q->dequeue_timer,
				q->remaining_space,
				p->energy,
				clients[i + 1] ? ", " : "\n");
	}
}

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
			print_client_queues(user_clients);
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
