#include "server.h"

static void one_team_wins(int team_id)
{
	printf("team '%s' won!\n", g_opts.team_names[team_id]);
}

static void	many_teams_win(int num_winners, int *team_ids)
{
	int		i;

	printf("It's a tie! %d teams won:\n", num_winners);
	i = 0;
	while (i < num_winners)
	{
		printf("%s\n", g_opts.team_names[team_ids[i]]);
		++i;
	}
}

static void	everyone_loses(void)
{
	printf("Everyone died. No one wins.\n");
}

void	handle_possible_gameover(void)
{
	int		*winning_team_ids;
	int		num_winners;

	winning_team_ids = NULL;
	num_winners = get_winning_teams(&winning_team_ids);
	if (num_winners != 0)
	{
		if (num_winners == -1)
			everyone_loses();
		else if (num_winners == 1)
			one_team_wins(winning_team_ids[0]);
		else
			many_teams_win(num_winners, winning_team_ids);
		exit(0);
	}
	free(winning_team_ids);
}
