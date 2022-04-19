/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:20:41 by frrusso           #+#    #+#             */
/*   Updated: 2021/12/17 13:40:44 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_joinstr(char const *s, char *str, int i)
{
	size_t	j;

	if (!s)
		return (i);
	j = 0;
	while (s[j])
	{
		str[i + j] = s[j];
		j++;
	}
	return (i + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = ft_joinstr(s1, str, 0);
	i = ft_joinstr(s2, str, i);
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = ft_joinstr(s1, str, 0);
	i = ft_joinstr(s2, str, i);
	str[i] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*ft_strjoin_long(char *s1, char *s2, char *s3, char *s4)
{
	size_t	i;
	char	*str;

	i = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4) + 1;
	str = malloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	i = ft_joinstr(s1, str, 0);
	i = ft_joinstr(s2, str, i);
	i = ft_joinstr(s3, str, i);
	i = ft_joinstr(s4, str, i);
	str[i] = '\0';
	return (str);
}
