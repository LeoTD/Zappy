#include "server.h"
#include "player_type.h"
#include "client_type.h"
#include "tile_type.h"

#define MEANINGLESS_GFX_CLIENT_ID -1
#define GFX_CLIENT_SECRET_KEY "banana"

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

static int	team_id_if_slot_available(char *msg)
{
	int		open_slots;
	int		team_id;
	int		i;

	team_id = -1;
	i = 0;
	while (g_opts.team_names[i])
	{
		if (!strcmp(g_opts.team_names[i], msg))
		{
			team_id = i;
			break ;
		}
		++i;
	}
	if (team_id == -1 || (open_slots = get_team_open_slots(team_id)) == 0)
		return (-1);
	return (team_id);
}

static void	greet_user_client(int fd, int team_id)
{
	char	response[256];
	int		open_slots;

	open_slots = get_team_open_slots(team_id);
	snprintf(response, sizeof(response), "%d\n%d %d\n",
			open_slots, g_opts.world_width, g_opts.world_height);
	send(fd, response, strlen(response), 0);
}

static void send_command_tick_delays(int fd)
{
	gfx_sendone(fd, "DELAY_TIME SEE %d\n", get_cmdfunc_tick_delay(see));
	gfx_sendone(fd, "DELAY_TIME ADVANCE %d\n", get_cmdfunc_tick_delay(advance));
	gfx_sendone(fd, "DELAY_TIME RIGHT %d\n", get_cmdfunc_tick_delay(right));
	gfx_sendone(fd, "DELAY_TIME LEFT %d\n", get_cmdfunc_tick_delay(left));
	gfx_sendone(fd, "DELAY_TIME LEAD_RITUAL %d\n", get_cmdfunc_tick_delay(incantation_finish));
	gfx_sendone(fd, "DELAY_TIME KICK %d\n", get_cmdfunc_tick_delay(kick));
	gfx_sendone(fd, "DELAY_TIME BROADCAST %d\n", get_cmdfunc_tick_delay(broadcast));
	gfx_sendone(fd, "DELAY_TIME TAKE %d\n", get_cmdfunc_tick_delay(take));
	gfx_sendone(fd, "DELAY_TIME PUT %d\n", get_cmdfunc_tick_delay(put));
	gfx_sendone(fd, "DELAY_TIME LAY_EGG %d\n", get_cmdfunc_tick_delay(fork_player));
	gfx_sendone(fd, "DELAY_TIME EGG_HATCH %d\n", get_cmdfunc_tick_delay(fork_finish));
}

static void	gfx_eventmsg_greeting(int fd)
{
	t_player	*p;
	t_tile		*t;
	int			i;

	gfx_sendone(fd, "TICK %d\n", get_elapsed_ticks());
	gfx_sendone(fd, "WORLD %d %d %d\n", g_opts.world_width,
			g_opts.world_height, g_opts.tickrate);
	while ((t = iter_tiles()))
		gfx_sendone(fd, "TILE %d %d %d %d %d %d %d %d %d %d\n",
				t->x, t->y, t->eggs, t->count[FOOD],
				t->count[LINEMATE], t->count[DERAUMERE], t->count[SIBUR],
				t->count[MENDIANE], t->count[PHIRAS], t->count[THYSTAME]);
	i = 0;
	while (i < g_opts.teamcount)
		gfx_sendone(fd, "TEAMNAME %s\n", g_opts.team_names[i++]);
	while ((p = iter_players()))
		gfx_sendone(fd, "PLAYER %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
			p->id, p->team_id, p->level, p->tile->x, p->tile->y, p->energy,
			p->facing, p->count[FOOD], get_client_by_id(p->id) != NULL,
			p->count[LINEMATE], p->count[DERAUMERE], p->count[SIBUR],
			p->count[MENDIANE], p->count[PHIRAS], p->count[THYSTAME]);
	send_command_tick_delays(fd);
	gfx_sendone(fd, "%s", "DONE\n");
}

void		complete_user_connection_handshake(int cli_fd)
{
	char				msg[MAX_TEAM_NAME_LENGTH + 1];
	int					team_id;
	int					player_id;

	if (recv(cli_fd, msg, MAX_TEAM_NAME_LENGTH, 0) <= 0)
	{
		fputs("cli_fd closed during handshake\n", stderr);
		socket_lookup_remove(cli_fd);
		close(cli_fd);
		return ;
	}
	msg[strcspn(msg, "\n")] = '\0';
	if (!strcmp(GFX_CLIENT_SECRET_KEY, msg))
	{
		register_client(cli_fd, MEANINGLESS_GFX_CLIENT_ID, GFX);
		gfx_eventmsg_greeting(cli_fd);
	}
	else if ((team_id = team_id_if_slot_available(msg)) != -1)
	{
		greet_user_client(cli_fd, team_id);
		player_id = assign_avatar(team_id);
		register_client(cli_fd, player_id, ACTIVE_PLAYER);
		gfx_sendall("CONNECT %d\n", player_id);
	}
}
