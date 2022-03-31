/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:48:50 by frrusso           #+#    #+#             */
/*   Updated: 2021/12/16 17:24:52 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_subsize(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	if (ft_strlen(s) - start < len)
		i = ft_strlen(s) - start;
	else
		i = len;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s || start > ft_strlen(s))
	{
		res = ft_calloc(1, 1);
		return (res);
	}
	res = malloc(sizeof(char) * (ft_subsize(s, start, len) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
