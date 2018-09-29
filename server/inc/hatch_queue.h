#ifndef HATCH_QUEUE_H
# define HATCH_QUEUE_H

struct						s_player_egg
{
	int					x;
	int					y;
	int					team_id;
	int					timer;
	struct s_player_egg	*next;
};

struct						s_hatch_queue
{
	struct s_player_egg	*head;
	struct s_player_egg	*tail;
	int					length;
};

extern struct s_hatch_queue	g_hatch_queue;
#endif
