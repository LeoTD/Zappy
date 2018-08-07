#include "server.h"

int		test_stone_placement(void);
int		test_user_commands_runnable(void);
int		test_can_make_server_listener(void);

int		main(int argc, char **argv)
{
	test_stone_placement();
	test_user_commands_runnable();
	test_can_make_server_listener();
	return (0);
}
