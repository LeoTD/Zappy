#include "server.h"

struct s_opts	g_opts = { 0, 0, 0, 0, 0, 0, 0 };

static void		usage(void)
{
	char *msg;

	msg = "Usage: ./server -p <port> -x <width> -y <height> -n <team> \
[<team>] [<team>] ... -c <nb> -t <t>\n\
-p port number\n\
-x world width\n\
-y world height\n\
-n team_name_1 team_name_2 ...\n\
-c number of clients authorized at the beginning of the game\n\
-t time unit divider (the greater t is, the faster the game will go)\n";
	fputs(msg, stderr);
	exit(1);
}

static void		parse_team_names(char **argv)
{
	int		i;
	int		teamcount;

	i = 0;
	while (argv[i] && argv[i][0] != '-')
		++i;
	teamcount = i + 1;
	g_opts.team_names = malloc((teamcount + 1) * sizeof(char *));
	bzero(g_opts.team_names, (teamcount + 1) * sizeof(char *));
	g_opts.team_names[0] = optarg;
	i = 0;
	while (argv[i] && argv[i][0] != '-')
	{
		if (strlen(argv[i]) > MAX_TEAM_NAME_LENGTH)
		{
			fprintf(stderr, "Team name `%s' exceeds max length of %d\n",
					argv[i], MAX_TEAM_NAME_LENGTH);
			exit(1);
		}
		g_opts.team_names[i + 1] = argv[i];
		++i;
	}
	g_opts.teamcount = teamcount;
	optind += teamcount - 1;
}

int				team_name_to_id(char *name)
{
	int		i;

	i = 0;
	while (g_opts.team_names[i])
	{
		if (!strcmp(g_opts.team_names[i], name))
			return (i);
		i++;
	}
	return (-1);
}

static void		ensure_all_options_present(void)
{
	if (g_opts.server_port <= 0
			|| g_opts.world_height <= 0
			|| g_opts.world_width <= 0
			|| g_opts.initial_players_per_team <= 0
			|| g_opts.tickrate <= 0
			|| g_opts.team_names == NULL)
	{
		usage();
	}
}

void			parse_options(int argc, char **argv)
{
	char	ch;

	while ((ch = getopt(argc, argv, "p:x:y:n:c:t:")) != -1)
	{
		if (ch == 'p')
			g_opts.server_port = atoi(optarg);
		else if (ch == 'x')
			g_opts.world_width = atoi(optarg);
		else if (ch == 'y')
			g_opts.world_height = atoi(optarg);
		else if (ch == 'c')
			g_opts.initial_players_per_team = atoi(optarg);
		else if (ch == 't')
			g_opts.tickrate = atoi(optarg);
		else if (ch == 'n')
			parse_team_names(argv + optind);
		else
			usage();
	}
	if (g_opts.tickrate <= 0)
		g_opts.tickrate = 100;
	ensure_all_options_present();
}
