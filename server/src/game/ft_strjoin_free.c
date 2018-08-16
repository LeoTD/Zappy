#include "server.h"

char	*ft_strjoin_free(char *str1, char *str2)
{
	str1 = realloc(str1, strlen(str1) + strlen(str2) + 1);
	str1 = strcpy(str1, str2);
	bzero(str2, strlen(str2));
	free(str2);
	return (str1);
}
