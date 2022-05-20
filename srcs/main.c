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

int	ft_environment(int ac, char **av, char **aenv)
{
	int	i;
	int	err;

	if (aenv)
		return (0);
	err = 0;
	i = 2;
	while (i < ac - 1)
	{
		if (access(av[i], X_OK) == -1)
		{
			ft_perror(av[i]);
			err = 1;
		}
		i++;
	}
	return (err);
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

int	ft_return(int fd[2])
{
	ft_close_main(fd);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **aenv)
{
	int		fd[2];
	t_cmd	*cmd;

	if (ft_environment(ac, av, aenv))
		return (EXIT_FAILURE);
	if (ac < 5)
		return (ft_write("Usage : ./pipex file1 cmd1 cmd2 ... file2\n"));
	fd[1] = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 00644);
	if (fd[1] == -1)
		return (ft_write_err(av[ac - 1]));
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_perror(av[1]);
	cmd = ft_init_cmd(ac, av);
	if (!cmd)
		return (ft_return(fd));
	pipex(fd, cmd, aenv);
	ft_close_main(fd);
	ft_cmdfree(cmd);
	return (EXIT_SUCCESS);
}
