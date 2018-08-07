#include "server.h"

int		test_stone_placement(void);
int		test_user_commands_runnable(void);
int		test_can_make_server_listener(void);
int		test_server_listens_for_clients(void);

int		main(int argc, char **argv)
{
	test_stone_placement();
	test_user_commands_runnable();
	test_can_make_server_listener();
	test_server_listens_for_clients();
	return (0);
}
