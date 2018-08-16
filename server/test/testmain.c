#include "server.h"

int		test_map_creation(void);
int		test_map_movement(void);
int		test_player_creation(void);
int		test_player_movement(void);

int		main(int argc, char **argv)
{
	test_map_creation();
	test_map_movement();
	test_player_creation();
	test_player_movement();
	return (0);
}
