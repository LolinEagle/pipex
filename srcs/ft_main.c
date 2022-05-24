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

void	ft_close_pipe(t_pipe *pip)
{
	while (pip != NULL)
	{
		close(pip->pipe[0]);
		close(pip->pipe[1]);
		pip = pip->next;
	}
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
