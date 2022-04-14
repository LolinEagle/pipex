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

void	pipex_child(int fd, int end[2], t_cmd *cmd, char **aenv)
{
	int		i;
	char	*path;
	char	**paths;

	if (dup2(end[1], 1) < 0)
		exit(EXIT_FAILURE);
	close(end[0]);
	if (dup2(fd, 0) < 0)
		exit(EXIT_FAILURE);
	paths = ft_find_paths(aenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_gnl(path, cmd->cmd[0]);
		execve(path, cmd->cmd, aenv);
		free(path);
	}
	if (paths)
		ft_free_split(paths);
	ft_cmdfree(cmd);
	exit(EXIT_FAILURE);
}

void	pipex_parent(int fd, int end[2], t_cmd *cmd, char **aenv)
{
	int		i;
	char	*path;
	char	**paths;
	int		wstatus;

	wait(&wstatus);
	if (dup2(end[0], 0) < 0)
		return ;
	close(end[1]);
	if (dup2(fd, 1) < 0)
		return ;
	paths = ft_find_paths(aenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_gnl(path, cmd->cmd[0]);
		execve(path, cmd->cmd, aenv);
		free(path);
	}
	if (paths)
		ft_free_split(paths);
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
