#include "server.h"

int		test_map_creation(void);
int		test_map_movement(void);
int		test_player_creation(void);
int		test_player_movement(void);
int		test_user_commands_runnable(void);
int		test_can_make_server_listener(void);
int		test_server_listens_for_clients(void);

int		main(int argc, char **argv)
{
	test_map_creation();
	test_map_movement();
	test_player_creation();
	test_player_movement();
//	test_user_commands_runnable();
//	test_can_make_server_listener();
//	test_server_listens_for_clients();
	return (0);
}
