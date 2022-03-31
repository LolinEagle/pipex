/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:38:38 by frrusso           #+#    #+#             */
/*   Updated: 2021/12/17 13:42:51 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char const *s, char c)
{
	int	i;
	int	j;
	int	r;

	i = 0;
	j = 1;
	r = 0;
	while (s[i])
	{
		if (j && s[i] != c)
		{
			j = 0;
			r++;
		}
		if (!j && s[i] == c)
			j = 1;
		i++;
	}
	return (r);
}

int	ft_len(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (j);
		i++;
		j++;
	}
	return (j);
}

char	*ft_input(char const *s, char c, int i)
{
	int		j;
	char	*word;

	word = malloc(sizeof(char) * (ft_len(s, c, i) + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (s[i] && s[i] != c)
	{
		word[j] = s[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			res[j] = ft_input(s, c, i);
		else
			break ;
		while (s[i] && s[i] != c)
			i++;
		j++;
	}
	res[j] = NULL;
	return (res);
}
