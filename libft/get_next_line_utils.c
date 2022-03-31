/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:14:58 by frrusso           #+#    #+#             */
/*   Updated: 2022/01/19 11:15:04 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (s1 && s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[i + j] = s2[i];
		i++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}
