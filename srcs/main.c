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
	res->cmd = ft_split(cmd, ' ');
	res->next = NULL;
	return (res);
}

void	ft_cmdfree(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp)
	{
		i = -1;
		while (cmd->cmd[++i])
			free(cmd->cmd[i]);
		free(cmd->cmd);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	i = -1;
	while (cmd->cmd[++i])
		free(cmd->cmd[i]);
	free(cmd->cmd);
	free(cmd);
}

int	ft_return(t_cmd *cmd)
{
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

	if (ac != 5)
		return (ft_write("Usage : ./pipex file1 cmd1 cmd2 file2\n"));
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 00644);
	if (!fd[0] || !fd[1])
		return (EXIT_FAILURE);
	cmd = ft_cmdnew(av[2]);
	if (!cmd)
		return (EXIT_FAILURE);
	cmd->next = ft_cmdnew(av[3]);
	if (!cmd->next)
		return (ft_return(cmd));
	pipex(fd, cmd, aenv);
	ft_cmdfree(cmd);
	return (EXIT_SUCCESS);
}
