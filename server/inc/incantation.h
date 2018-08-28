#ifndef INCANTATION_H
# define INCANTATION_H

struct s_incant_args
{
	int		player_id;
	int		*levelup_group;
	int		group_size;
	int		new_level;
};

struct s_incant_req
{
	int		group_size;
	int		stones[6];
};
#endif
