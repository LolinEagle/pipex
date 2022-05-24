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

t_pipe	*ft_pipe_last(t_pipe *pipefd)
{
	while (pipefd->next)
		pipefd = pipefd->next;
	return (pipefd);
}

int	pipex_fork(int fd[2], t_pipe *pipefd, t_cmd *cmd, char **aenv)
{
	int		i;
	pid_t	child;

	i = -1;
	while (pipefd->ac > 5 && ++i < pipefd->ac - 4)
	{
		child = fork();
		if (child < 0)
			return (1);
		if (!child)
			pipex_child(fd, pipefd->pipe, cmd, aenv);
		pipefd = pipefd->next;
	}
	return (0);
}

void	pipex(int fd[2], t_cmd *cmd, int ac, char **aenv)
{
	int		i;
	int		wstatus;
	t_pipe	*pipefd;
	pid_t	child;

	pipefd = ft_init_pipe(ac);
	child = fork();
	if (child < 0)
		return ;
	if (!child)
		pipex_child0(fd, pipefd->pipe, cmd, aenv);
	if (pipex_fork(fd, pipefd->next, cmd, aenv))
		return ;
	child = fork();
	if (child < 0)
		return ;
	if (!child)
		pipex_child1(fd, ft_pipe_last(pipefd)->pipe, cmd, aenv);
	ft_close_pipe(pipefd);
	i = -1;
	while (++i < ac - 3)
		wait(&wstatus);
	ft_pipefree(pipefd);
}
