/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:22:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/03/31 12:22:38 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_return(t_cmd *cmd, int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	if (cmd)
		ft_cmdfree(cmd);
	return (EXIT_FAILURE);
}

int	ft_write(char *str)
{
	size_t	count;

	count = ft_strlen(str);
	write(1, str, count);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **aenv)
{
	int		fd[2];
	t_cmd	*cmd;

	if (!aenv)
		return (ft_write("No environment found\n"));
	if (ac != 5)
		return (ft_write("Usage : ./pipex file1 cmd1 cmd2 file2\n"));
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_perror(av[1]);
	fd[1] = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 00644);
	if (fd[1] == -1)
		ft_perror(av[ac - 1]);
	cmd = ft_cmdnew(av[2]);
	if (!cmd)
		return (ft_return(cmd, fd));
	cmd->next = ft_cmdnew(av[3]);
	if (!cmd->next)
		return (ft_return(cmd, fd));
	pipex(fd, cmd, aenv);
	close(fd[0]);
	close(fd[1]);
	ft_cmdfree(cmd);
	return (EXIT_SUCCESS);
}
