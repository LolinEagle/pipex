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

void	pipex_child(int fd, int end[2], t_cmd *cmd, char **aenv)
{
	char	*path;

	ft_printf("fd=%i cmd->cmd=%s\n", fd, cmd->cmd[0]);
	// if (dup2(fd, 0) < 0 || dup2(1, end[1]) < 0)
	// 	exit(EXIT_FAILURE);
	// close(end[0]);
	// close(fd);
	// path = ft_strjoin("/usr/bin/", cmd->cmd[0]);
	// execve(path, cmd->cmd, aenv);
	// free(path);
	exit(EXIT_SUCCESS);
}

void	pipex_parent(int fd, int end[2], t_cmd *cmd, char **aenv)
{
	char	*path;
	int		wstatus;

	wait(&wstatus);
	ft_printf("fd=%i cmd->cmd=%s\n", fd, cmd->cmd[0]);
	// if (dup2(end[0], 0) < 0 || dup2(1, fd) < 0)
	// 	return ;
	// close(end[1]);
	// close(fd);
	// path = ft_strjoin("/usr/bin/", cmd->cmd[0]);
	// execve(path, cmd->cmd, aenv);
	// free(path);
	return ;
}

void	pipex(int fd[2], t_cmd *cmd, char **aenv)
{
	int		end[2];
	pid_t	parent;

	if (pipe(end) < 0)
		return ;
	parent = fork();
	if (parent < 0)
		return ;
	if (!parent)
		pipex_child(fd[0], end, cmd, aenv);
	else
		pipex_parent(fd[1], end, cmd->next, aenv);
}
