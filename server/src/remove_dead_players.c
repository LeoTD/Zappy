#include "server.h"
#include "client_type.h"

void	send_death_message(int sock_fd)
{
	if (send(sock_fd, "death\n", strlen("death\n"), 0) <= 0)
		perror("send death message");
}

void	remove_dead_players(void)
{
	int			*player_ids;
	int			pid_count;
	t_client	*client;
	int			i;

	player_ids = get_dead_players(&pid_count);
	i = 0;
	while (i < pid_count)
	{
		client = get_client_by_player_id(player_ids[i]);
		if ((client = get_client_by_player_id(player_ids[i])))
		{
			send_death_message(client->socket_fd);
			socket_lookup_remove(client->socket_fd);
			unregister_client_by_player_id(player_ids[i]);
		}
		++i;
	}
}
