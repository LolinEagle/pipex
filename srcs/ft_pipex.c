/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:40:01 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/19 13:40:03 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_strtolower(char *s)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		s[i] = ft_tolower(s[i]);
		i++;
	}
}

void	ft_perror(char *arg)
{
	size_t	count;
	char	*str;

	str = ft_strjoin_long("pipex: ", strerror(errno), ": ", arg);
	ft_strtolower(str);
	str = ft_strjoin_free(str, "\n");
	count = ft_strlen(str);
	write(2, str, count);
	free(str);
}

void	ft_perror_cmd(char *arg)
{
	size_t	count;
	char	*str;

	str = ft_strjoin("pipex: command not found: ", arg);
	str = ft_strjoin_free(str, "\n");
	count = ft_strlen(str);
	write(2, str, count);
	free(str);
}

char	*ft_is_path(char *aenv)
{
	int		i;
	char	*path;

	path = "PATH=";
	i = 0;
	while (path[i] && aenv[i] == path[i])
		i++;
	if (!path[i])
		return (aenv + ft_strlen(path));
	return (NULL);
}

char	**ft_find_paths(char **aenv)
{
	int		i;
	char	*path;

	path = NULL;
	i = -1;
	while (aenv[++i] && !path)
		path = ft_is_path(aenv[i]);
	if (path)
		return (ft_split(path, ':'));
	return (NULL);
}
