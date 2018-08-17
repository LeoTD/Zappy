#include "server.h"
#include "test.h"

int		test_map_creation(void);
int		test_map_movement(void);
int		test_player_creation(void);
int		test_player_movement(void);

void	test_client_connection_listener(void);

int		main(int argc, char **argv)
{
	puts("hello world");
	test_client_connection_listener();
	/* test_map_creation(); */
	/* test_map_movement(); */
	/* test_player_creation(); */
	/* test_player_movement(); */
	return (0);
}
