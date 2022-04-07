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

t_cmd	*ft_cmdnew(char *cmd)
{
	t_cmd	*res;

	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->cmd = ft_split(cmp, ' ');
	res->next = NULL;
	return (res);
}

void	ft_cmdfree(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp)
	{
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	free(cmd);
}

int	main(int ac, char **av, char **aenv)
{
	int		fd[2];
	t_cmd	*pipex;

	if (ac == 5)
	{
		ft_printf("< %s %s | %s > %s\n", av[1], av[2], av[3], av[4]);
		fd[0] = open(av[1], O_RDONLY);
		fd[1] = open(av[4], O_WRONLY);
		pipex = ft_cmdnew(av[2]);
		pipex->next = ft_cmdnew(av[3]);
		ft_printf("%i %i %s %s\n", fd[0], fd[1], pipex->cmd, pipex->next->cmd);
		pipex()
		ft_cmdfree(pipex);
	}
	else
		return (write(1, "Usage : ./pipex file1 cmd1 cmd2 file2\n", 38));
	return (0);
}
