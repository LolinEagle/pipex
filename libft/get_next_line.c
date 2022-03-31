/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:14:43 by frrusso           #+#    #+#             */
/*   Updated: 2022/01/19 11:14:46 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char *tmp)
{
	int		i;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	i = 1;
	while (!ft_strchr(tmp, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
		{
			free(tmp);
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		tmp = ft_strjoin_gnl(tmp, buff);
	}
	free(buff);
	return (tmp);
}

char	*ft_get_line(char *tmp)
{
	int		i;
	char	*s;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (tmp[++i] && tmp[i] != '\n')
		s[i] = tmp[i];
	if (tmp[i] == '\n')
	{
		s[i] = tmp[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_save(char *tmp)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(tmp) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (tmp[i])
		s[c++] = tmp[i++];
	s[c] = '\0';
	free(tmp);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*tmp[256];
	char		*res;

	if (fd < 0 || fd > 255 || BUFFER_SIZE < 1)
		return (NULL);
	tmp[fd] = ft_read(fd, tmp[fd]);
	if (!tmp[fd])
		return (NULL);
	res = ft_get_line(tmp[fd]);
	tmp[fd] = ft_save(tmp[fd]);
	return (res);
}
