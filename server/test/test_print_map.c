#include "server.h"

void		print_map(void)
{
	t_tile		*t;
	int			x, y;
	char		str[255];
	char		*pstr[] = {
		"Coords",
		"Players",
		"Food",
		"Stone type 0",
		"Stone type 1",
		"Stone type 2",
		"Stone type 3",
		"Stone type 4",
		"Stone type 5"
	};

	x = -1;
	y = -1;
	for (int type = 1; type < 9; type++)
	{
		printf("Showing %s:\n", pstr[type]);
		while (++y < g_map->y)
		{
			while (++x < g_map->x)
			{
				t = &g_map->tile[x][y];
				switch (type)
				{
					case 1 :
						printf("%3d ", t->num_players);
						break ;
					case 2 :
						printf("%3d ", t->food);
						break ;
					case 3 :
						printf("%3d ", t->stones[0]);
						break ;
					case 4 :
						printf("%3d ", t->stones[1]);
						break ;
					case 5 :
						printf("%3d ", t->stones[2]);
						break ;
					case 6 :
						printf("%3d ", t->stones[3]);
						break ;
					case 7 :
						printf("%3d ", t->stones[4]);
						break ;
					case 8 :
						printf("%3d ", t->stones[5]);
						break ;
					default :
						printf("(%2d, %2d) ", t->x, t->y);
				}
			}
			x = -1;
			printf("\n\n");
		}
		y = -1;
		printf("Press Enter for next entity type.\n");
		for (int i = 0; i < (g_map->y + 1) * 2; i++)
			printf("\033[1A\033[2K");
		printf("\033[1A\033[2K");
		read(0, &str, 1);
	}
}
