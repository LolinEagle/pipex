/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:51:46 by frrusso           #+#    #+#             */
/*   Updated: 2021/12/07 12:46:30 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	i = size;
	while (i-- != 0 && *d != '\0')
		d++;
	dstlen = d - dst;
	i = size - dstlen;
	if (i == 0)
		return (dstlen + ft_strlen(s));
	while (*s != '\0')
	{
		if (i != 1)
		{
			*d++ = *s;
			i--;
		}
		s++;
	}
	*d = '\0';
	return (dstlen + (s - src));
}
