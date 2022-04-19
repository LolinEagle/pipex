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
