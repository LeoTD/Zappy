#include "server.h"

//Temp var until exists in system
int		g_winning_team_id = 0;

/* Prototype func does not exist yet
**		if gameover, returns winning team ID or -1 if all dead
**		else returns 0
** Expect function in Game Logic. game/something.c
*/
/*
int		logic_game_over(void);

** int		is_game_over(int *winning_team_id_ptr)
** {
** 	g_winning_team_id = logic_game_over();
** 	return (g_winning_team_id ? 1 : 0);
** }
*/

int		is_game_over(int *winning_team_id_ptr)
{
	(void)winning_team_id_ptr;
	return (0);
}

void	handle_game_over(int winning_team_id)
{
	(void)winning_team_id;
	return ;
}
