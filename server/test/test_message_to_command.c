#include "server.h"

t_cmdfunc	string_to_command_fn_unary(char *, char **);
t_cmdfunc	string_to_command_fn_nullary(char *);
int			enqueue_received_commands(char *, int);

int		test_string_to_command_fn()
{
	char		*arg;
	t_cmdfunc	cmdfunc;
	char		cmd_str[255] = {0};

	strcpy(cmd_str, "advance");
	assert(string_to_command_fn_nullary(cmd_str) == advance);
	strcpy(cmd_str, "fork");
	assert(string_to_command_fn_nullary(cmd_str) == fork_player);
	strcpy(cmd_str, "incantation");
	assert(string_to_command_fn_nullary(cmd_str) == incantation);
	strcpy(cmd_str, "inventory");
	assert(string_to_command_fn_nullary(cmd_str) == inventory);
	strcpy(cmd_str, "kick");
	assert(string_to_command_fn_nullary(cmd_str) == kick);
	strcpy(cmd_str, "left");
	assert(string_to_command_fn_nullary(cmd_str) == left);
	strcpy(cmd_str, "right");
	assert(string_to_command_fn_nullary(cmd_str) == right);
	strcpy(cmd_str, "see");
	assert(string_to_command_fn_nullary(cmd_str) == see);

	strcpy(cmd_str, "broadcast a string");
	cmdfunc = string_to_command_fn_unary(cmd_str, &arg);
	assert(cmdfunc == broadcast);
	assert(!strcmp("a string", arg));

	strcpy(cmd_str, "put phiras");
	cmdfunc = string_to_command_fn_unary(cmd_str, &arg);
	assert(cmdfunc == put);
	assert(!strcmp("phiras", arg));

	strcpy(cmd_str, "take deraumere");
	cmdfunc = string_to_command_fn_unary(cmd_str, &arg);
	assert(cmdfunc == take);
	assert(!strcmp("deraumere", arg));

	strcpy(cmd_str, "not a command");
	strcpy(arg, "initial arg value");
	cmdfunc = string_to_command_fn_unary(cmd_str, &arg);
	assert(cmdfunc == NULL);
	assert(!strcmp(arg, "initial arg value"));

	strcpy(cmd_str, "seeeeeeee");
	strcpy(arg, "initial arg value");
	cmdfunc = string_to_command_fn_unary(cmd_str, &arg);
	assert(cmdfunc == NULL);
	assert(!strcmp(arg, "initial arg value"));

	printf("%s: ok\n", __func__);
	return (0);
}

int		test_server_correctly_interprets_command_messages()
{
	puts("crappy test of command interpretation with stub scheduler follows:");
	char msg[] = "inventory\nfork\nincantation\nadvance\ntake phiras\nnotacommand\nput deraumere\ntake verylongnonexistentrock\nincomplete";
	enqueue_received_commands(msg, 1);
	return (0);
}
