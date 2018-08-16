/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:07:25 by eliu              #+#    #+#             */
/*   Updated: 2016/11/15 21:40:37 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
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
