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

void	ft_close_main(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	close(fd[1]);
}

void	ft_close(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
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
