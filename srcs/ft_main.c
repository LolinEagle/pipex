/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:42:58 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/14 14:43:00 by frrusso          ###   ########.fr       */
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

void	ft_free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

t_cmd	*ft_cmdnew(char *cmd)
{
	t_cmd	*res;

	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->cmd = ft_split(cmd, ' ');
	res->next = NULL;
	return (res);
}

void	ft_cmdfree(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp)
	{
		ft_free_split(cmd->cmd);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	ft_free_split(cmd->cmd);
	free(cmd);
}
