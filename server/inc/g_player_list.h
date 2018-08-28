#ifndef G_PLAYER_LIST_H
# define G_PLAYER_LIST_H

# include "server.h"
# include "player_type.h"

// XXX: temporarily increased to a large value because seemingly unrelated
// tests segfault if it's not huge.
# define START_SIZE MAX_CLIENTS * 10

t_player        **g_player_list;
int             g_list_size;

#endif
