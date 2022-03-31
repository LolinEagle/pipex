/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:34:44 by frrusso           #+#    #+#             */
/*   Updated: 2021/12/17 11:16:39 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dests;
	char	*srcs;
	char	*dlast;
	char	*slast;

	if (!dest && !src)
		return (NULL);
	dests = dest;
	srcs = (char *)src;
	if (dests < srcs)
	{
		while (n--)
			*dests++ = *srcs++;
	}
	else
	{
		slast = srcs + (n - 1);
		dlast = dests + (n - 1);
		while (n--)
			*dlast-- = *slast--;
	}
	return (dest);
}
