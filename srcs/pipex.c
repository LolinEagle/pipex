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

void	pipex_child0(int fd[2], int end[2], t_cmd *cmd, char **aenv)
{
	int		i;
	char	*path;
	char	**paths;

	close(fd[1]);
	close(end[0]);
	if (dup2(fd[0], 0) < 0)
		exit(EXIT_FAILURE);
	close(fd[0]);
	if (dup2(end[1], 1) < 0)
		exit(EXIT_FAILURE);
	paths = ft_find_paths(aenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_gnl(path, cmd->cmd[0]);
		if (access(path, X_OK) == 0)
			execve(path, cmd->cmd, aenv);
		free(path);
	}
	ft_perror(cmd->cmd[0]);
	if (paths)
		ft_free_split(paths);
	ft_cmdfree(cmd);
	close(end[1]);
	exit(EXIT_FAILURE);
}

void	pipex_child1(int fd[2], int end[2], t_cmd *cmd, char **aenv)
{
	int		i;
	char	*path;
	char	**paths;

	close(end[1]);
	if (dup2(end[0], 0) < 0)
		exit(EXIT_FAILURE);
	if (dup2(fd[1], 1) < 0)
		exit(EXIT_FAILURE);
	paths = ft_find_paths(aenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_gnl(path, cmd->cmd[0]);
		if (access(path, X_OK) == 0)
			execve(path, cmd->cmd, aenv);
		free(path);
	}
	ft_perror(cmd->cmd[0]);
	if (paths)
		ft_free_split(paths);
	ft_cmdfree(cmd);
	close(fd[1]);
	exit(EXIT_FAILURE);
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
		pipex_child1(fd, pipefd, cmd->next, aenv);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(&wstatus[0]);
	wait(&wstatus[1]);
}
