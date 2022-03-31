/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:16:15 by frrusso           #+#    #+#             */
/*   Updated: 2021/12/07 15:33:45 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*sbig;
	char		*slittle;

	sbig = (char *)big;
	slittle = (char *)little;
	i = 0;
	if (slittle[i] == '\0')
		return (sbig);
	while (i < len && sbig[i])
	{
		j = 0;
		while (i + j < len && sbig[i + j] == slittle[j])
		{
			j++;
			if (slittle[j] == '\0')
				return (sbig + i);
		}
		i++;
	}
	return (NULL);
}
