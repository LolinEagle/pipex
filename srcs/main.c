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

int	ft_environment(char **av, char **aenv)
{
	if (aenv)
		return (0);
	else
	{
		if (access(av[2], X_OK) == -1)
			ft_perror(av[2]);
		if (access(av[3], X_OK) == -1)
			ft_perror(av[3]);
		if (access(av[2], X_OK) == 0 || access(av[3], X_OK) == 0)
			return (0);
	}
	return (1);
}

int	ft_write(char *str)
{
	size_t	count;

	count = ft_strlen(str);
	write(1, str, count);
	return (EXIT_FAILURE);
}

int	ft_write_err(char *str)
{
	ft_perror(str);
	return (EXIT_FAILURE);
}

int	ft_return(t_cmd *cmd, int fd[2])
{
	ft_close_main(fd);
	if (cmd)
		ft_cmdfree(cmd);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **aenv)
{
	int		fd[2];
	t_cmd	*cmd;

	if (ft_environment(av, aenv))
		return (EXIT_FAILURE);
	if (ac != 5)
		return (ft_write("Usage : ./pipex file1 cmd1 cmd2 file2\n"));
	fd[1] = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 00644);
	if (fd[1] == -1)
		return (ft_write_err(av[ac - 1]));
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_perror(av[1]);
	cmd = ft_cmdnew(av[2]);
	if (!cmd)
		return (ft_return(cmd, fd));
	cmd->next = ft_cmdnew(av[3]);
	if (!cmd->next)
		return (ft_return(cmd, fd));
	pipex(fd, cmd, aenv);
	ft_close_main(fd);
	ft_cmdfree(cmd);
	return (EXIT_SUCCESS);
}
