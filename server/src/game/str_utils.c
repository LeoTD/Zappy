#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*strnew(char *str)
{
	char	*new;

	new = (char*)malloc(sizeof(char) * strlen(str) + 1);
	new = strcpy(new, str);
	return (new);
}

char	*strjoin_free(char *str1, char *str2)
{
	str1 = realloc(str1, strlen(str1) + strlen(str2) + 1);
	str1 = strcpy(str1, str2);
	bzero(str2, strlen(str2));
	free(str2);
	return (str1);
}

char	*itoa(int n)
{
	char			*str;
	int				len;
	int				temp;
	unsigned int	u;

	len = 1;
	temp = n;
	while (temp /= 10)
		len++;
	if (n < 0)
		len++;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	u = (unsigned int)n;
	if (n < 0)
	{
		str[0] = '-';
		u *= -1;
	}
	str[len] = '\0';
	str[--len] = (u % 10) + '0';
	while (u /= 10)
		str[--len] = (u % 10) + '0';
	return (str);
}
