#include "server.h"

static int	string_to_team_id(char *str)
{
	int		i;

	i = 0;
	while (g_opts.team_names[i])
	{
		if (!strcmp(g_opts.team_names[i], str))
			return (i);
		++i;
	}
	return (-1);
}

static void	abort_handshake(int fd)
{
	socket_lookup_remove(fd);
	close(fd);
}

void		initiate_user_connection_handshake(int serv_fd)
{
	int					cli_fd;
	struct sockaddr_in	client_addr;
	socklen_t			len;

	len = sizeof(struct sockaddr);
	if ((cli_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &len)) == -1)
		perror("handshake accept");
	else
	{
		if (send(cli_fd, "WELCOME\n", 8, 0) == -1)
			perror("send welcome");
		else
			socket_lookup_add(cli_fd, HANDSHAKE);
	}
}

static int assign_avatar(int team, int *num_open_slots_ptr)
{
	// TODO: remove when this is a real game function call!
	*num_open_slots_ptr = 2;
	return (30);
}

static int	assign_to_team_if_slot_available(int sock_fd, int team_id)
{
	int		player_id;
	int		open_slots;
	char	response[256];

	if ((player_id = assign_avatar(team_id, &open_slots)) == -1)
		return (-1);
	register_user_client(sock_fd, player_id);
	snprintf(response, sizeof(response), "%d\n%d %d\n",
			open_slots, g_opts.world_width, g_opts.world_height);
	if (send(sock_fd, response, strlen(response), 0) == -1)
	{
		// tell the game to free this body again and return -1?
		// or just hope this never happens
		perror("send nb-client/worldsize");
	}
	return (player_id);
}

void		complete_user_connection_handshake(int cli_fd)
{
	char				msg[MAX_TEAM_NAME_LENGTH + 1];
	int					team_id;
	ssize_t				count;
	char				*nl;

	if ((count = recv(cli_fd, msg, MAX_TEAM_NAME_LENGTH, 0)) == -1)
		perror("handshake recv");
	if (count <= 0)
	{
		fputs("client disconnected mid-handshake\n", stderr);
		abort_handshake(cli_fd);
		return ;
	}
	if (!(nl = strchr(msg, '\n')))
		abort_handshake(cli_fd);
	*nl = '\0';
	if ((team_id = string_to_team_id(msg)) == -1)
		abort_handshake(cli_fd);
	else if ((assign_to_team_if_slot_available(cli_fd, team_id)) == -1)
		abort_handshake(cli_fd);
}
