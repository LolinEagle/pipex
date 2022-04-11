/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:22:48 by frrusso           #+#    #+#             */
/*   Updated: 2022/03/31 12:22:51 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_child(int fd, int end[2], t_cmd *cmd)
{
	ft_printf("%i %s\n", fd, cmd->cmd[0]);
	if (dup2(fd, 0) < 0 || dup2(end[1], 1))
		exit(EXIT_FAILURE);
	close(end[0]);
	close(fd);
	exit(EXIT_SUCCESS);
}

void	pipex_parent(int fd, int end[2], t_cmd *cmd)
{
	int	wstatus;

	wait(&wstatus);
	ft_printf("%i %s\n", fd, cmd->cmd[0]);
	if (dup2(fd, 1) < 0 || dup2(end[0], 0))
		return ;
	close(end[1]);
	close(fd);
	return ;
}

void	pipex(int fd[2], t_cmd *cmd)
{
	int		end[2];
	pid_t	parent;

	ft_printf("%i %i %s %s\n", fd[0], fd[1], cmd->cmd[0], cmd->next->cmd[0]);
	if (pipe(end) == -1)
		return ;
	parent = fork();
	if (parent < 0)
		return ;
	if (!parent)
		pipex_child(fd[0], end, cmd);
	else
		pipex_parent(fd[1], end, cmd->next);
}
