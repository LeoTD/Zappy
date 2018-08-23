#ifndef TESTING
# define TESTING
# include <fcntl.h>
# include <sys/resource.h>

extern int g_make_server_die;
extern int g_server_fd;
extern char system_sprintf_buf[4096];

#define fork_and_call_system(format, ...)\
	if (!fork()) {\
		sprintf(system_sprintf_buf, format, __VA_ARGS__);\
		system(system_sprintf_buf);\
		exit(0);\
	}

// helpers.c
int	get_port_from_fd(int fd);
int get_server_port(void);
void test_server_listen(void);
void quicksleep(void);
int string_equal_file_contents(char *expect_string, char *filepath);
void start_game_with_fake_options(void);
#endif
