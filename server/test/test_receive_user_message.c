#include "server.h"
#include "command_type.h"
#include "command_queue_type.h"
#include "client_type.h"
#include "test.h"

t_command *message_extract_next_command(char *msg, char **msg_next);
void enqueue_commands_from_user_message(t_client *c, char *msg);

void	test_extracts_valid_commands_from_buffer(void)
{
	char well_formatted_commands[] = "advance\n\
right\n\
left\n\
see\n\
inventory\n\
take something\n\
put something\n\
kick\n\
broadcast something\n\
incantation\n\
fork\n\
connect_nbr\n";

	char nonsense_commands[] = "advance something\n\
right!\n\
left!\n\
seE\n\
inventory inventory\n\
take\n\
put\n\
kick with an argument\n\
broadcast\n\
 fork\n\
connect_nbr \n\
\n\
see"; // <-- no newline

	t_cmdfunc expect_well_formatted_result[] = { advance, right, left, see,
		inventory, take, put, kick, broadcast, incantation,
		fork_player, connect_nbr, NULL };

	int i = 0;
	char *msg = well_formatted_commands;
	char *next = NULL;
	t_cmdfunc f;
	while ((f = expect_well_formatted_result[i]))
	{
		t_command *c = message_extract_next_command(msg, &next);
		assert(c && c->cmdfunc == f);
		msg = next;
		++i;
	}
	assert(i == 12);

	msg = nonsense_commands;
	next = NULL;
	for (int i = 0; i < 13; i++)
	{
		assert(message_extract_next_command(msg, &next) == NULL);
		msg = next;
	}
}

void	test_enqueues_commands_from_message_correctly(void)
{
	char msg[] = "connect_nbr\n\
kick\n\
forgot the newline on the next one:\n\
see";
	t_client *c = new_client(0, 0, ACTIVE_PLAYER);
	c->cmdqueue->remaining_space = 3;
	enqueue_commands_from_user_message(c, msg);
	assert(c->cmdqueue->remaining_space == 1);
	assert(c->cmdqueue->tail->cmd->cmdfunc == kick);
	char msg2[] = "nope\n\
take thystame\n\
inventory\n";
	enqueue_commands_from_user_message(c, msg2);
	assert(c->cmdqueue->tail->cmd->cmdfunc == take);
	assert(c->cmdqueue->remaining_space == 0);
}

void test_receive_user_message(void)
{
	test_extracts_valid_commands_from_buffer();
	test_enqueues_commands_from_message_correctly();
	printf("%s: ok\n", __FILE__);
}
