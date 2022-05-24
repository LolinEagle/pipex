/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:22:49 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/24 17:22:50 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex_child(char **cmd, char **aenv)
{
	int		i;
	char	*path;
	char	**paths;

	paths = ft_find_paths(aenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin_long(paths[i], "/", cmd[0], NULL);
		if (access(path, X_OK) == 0)
			execve(path, cmd, aenv);
		free(path);
	}
	ft_free_split(paths);
}

void	ft_free_child(int fd[2], int end[2], t_cmd *cmd)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (end[0] != -1)
		close(end[0]);
	if (end[1] != -1)
		close(end[1]);
	ft_cmdfree(cmd);
	exit(EXIT_FAILURE);
}

void	pipex_child0(int fd[2], int end[2], t_cmd *cmd, char **aenv)
{
	ft_close(fd[1], end[0]);
	if (dup2(fd[0], 0) < 0)
		ft_free_child(fd, end, cmd);
	ft_close(fd[0], -1);
	if (dup2(end[1], 1) < 0)
		ft_free_child(fd, end, cmd);
	close(end[1]);
	if (!aenv || ft_strchr(cmd->cmd[0], '/'))
		execve(cmd->cmd[0], cmd->cmd, aenv);
	else
		ft_pipex_child(cmd->cmd, aenv);
	ft_perror_cmd(cmd->cmd[0]);
	ft_free_child(fd, end, cmd);
}

void	pipex_child(int fd[2], int end[2], t_cmd *cmd, char **aenv)
{
	ft_close(fd[1], end[0]);
	if (dup2(fd[0], 0) < 0)
		ft_free_child(fd, end, cmd);
	ft_close(fd[0], -1);
	if (dup2(end[1], 1) < 0)
		ft_free_child(fd, end, cmd);
	close(end[1]);
	if (!aenv || ft_strchr(cmd->cmd[0], '/'))
		execve(cmd->cmd[0], cmd->cmd, aenv);
	else
		ft_pipex_child(cmd->cmd, aenv);
	ft_perror_cmd(cmd->cmd[0]);
	ft_free_child(fd, end, cmd);
}

void	pipex_child1(int fd[2], int end[2], t_cmd *cmd, char **aenv)
{
	ft_close(fd[0], end[1]);
	if (dup2(end[0], 0) < 0)
		ft_free_child(fd, end, cmd);
	close(end[0]);
	if (dup2(fd[1], 1) < 0)
		ft_free_child(fd, end, cmd);
	close(fd[1]);
	if (!aenv || ft_strchr(cmd->next->cmd[0], '/'))
		execve(cmd->next->cmd[0], cmd->next->cmd, aenv);
	else
		ft_pipex_child(cmd->next->cmd, aenv);
	ft_perror_cmd(cmd->next->cmd[0]);
	ft_free_child(fd, end, cmd);
}
