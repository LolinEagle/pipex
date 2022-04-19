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

void	ft_close(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
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
	int		i;
	char	*path;
	char	**paths;

	ft_close(fd[1], end[0]);
	if (dup2(fd[0], 0) < 0)
		ft_free_child(fd, end, cmd);
	ft_close(fd[0], -1);
	if (dup2(end[1], 1) < 0)
		ft_free_child(fd, end, cmd);
	close(end[1]);
	paths = ft_find_paths(aenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin_long(paths[i], "/", cmd->cmd[0], NULL);
		if (access(path, X_OK) == 0)
			execve(path, cmd->cmd, aenv);
		free(path);
	}
	if (paths)
		ft_free_split(paths);
	ft_perror_cmd(cmd->cmd[0]);
	ft_free_child(fd, end, cmd);
}

void	pipex_child1(int fd[2], int end[2], t_cmd *cmd, char **aenv)
{
	int		i;
	char	*path;
	char	**paths;

	ft_close(fd[0], end[1]);
	if (dup2(end[0], 0) < 0)
		ft_free_child(fd, end, cmd);
	close(end[0]);
	if (dup2(fd[1], 1) < 0)
		ft_free_child(fd, end, cmd);
	close(fd[1]);
	paths = ft_find_paths(aenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin_long(paths[i], "/", cmd->next->cmd[0], NULL);
		if (access(path, X_OK) == 0)
			execve(path, cmd->next->cmd, aenv);
		free(path);
	}
	if (paths)
		ft_free_split(paths);
	ft_perror_cmd(cmd->next->cmd[0]);
	ft_free_child(fd, end, cmd);
}

void	pipex(int fd[2], t_cmd *cmd, char **aenv)
{
	int		pipefd[2];
	pid_t	child[2];
	int		wstatus[2];

	if (pipe(pipefd) < 0)
		return ;
	child[0] = fork();
	if (child[0] < 0)
		return ;
	if (!child[0])
		pipex_child0(fd, pipefd, cmd, aenv);
	child[1] = fork();
	if (child[1] < 0)
		return ;
	if (!child[1])
		pipex_child1(fd, pipefd, cmd, aenv);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(&wstatus[0]);
	wait(&wstatus[1]);
}
