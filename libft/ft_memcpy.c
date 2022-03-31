/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:27:02 by frrusso           #+#    #+#             */
/*   Updated: 2021/12/17 11:15:11 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*str;
	const char	*res;

	if (!dest && !src)
		return (NULL);
	str = dest;
	res = src;
	i = 0;
	while (i < n)
	{
		str[i] = res[i];
		i++;
	}
	return (dest);
}
