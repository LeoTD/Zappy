#include "server.h"

char	*ft_strnew(char *str)
{
	char	*new;

	new = (char*)malloc(sizeof(char) * strlen(str) + 1);
	new = strcpy(new, str);
	return (new);
}
