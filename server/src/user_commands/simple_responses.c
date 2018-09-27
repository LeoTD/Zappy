#include "server.h"

char	*ok_response(void)
{
	char	*res;

	asprintf(&res, "ok\n");
	return (res);
}

char	*ko_response(void)
{
	char	*res;

	asprintf(&res, "ko\n");
	return (res);
}
