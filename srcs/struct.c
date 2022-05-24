/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:15:42 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/20 17:15:44 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_cmd_return(t_cmd *cmd)
{
	ft_cmdfree(cmd);
	return (NULL);
}

t_cmd	*ft_init_cmd(int ac, char **av)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = ft_cmdnew(av[2]);
	if (!cmd)
		return (NULL);
	tmp = cmd;
	i = 2;
	while (i < ac - 1)
	{
		tmp->next = ft_cmdnew(av[i]);
		if (!tmp->next)
			return (ft_cmd_return(cmd));
		tmp = tmp->next;
		i++;
	}
	return (cmd);
}

t_pipe	*ft_init_pipe(int ac)
{
	int		i;
	t_pipe	*pip;
	t_pipe	*tmp;

	pip = ft_pipenew(ac);
	if (!pip)
		return (NULL);
	tmp = pip;
	i = 0;
	while (i < ac - 4)
	{
		tmp->next = ft_pipenew(ac);
		if (!tmp->next)
		{
			ft_pipefree(pip);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	return (pip);
}

t_pipe	*ft_pipenew(int ac)
{
	t_pipe	*res;

	res = malloc(sizeof(t_pipe));
	if (!res)
		return (NULL);
	if (pipe(res->pipe) < 0)
	{
		free(res);
		return (NULL);
	}
	res->ac = ac;
	res->next = NULL;
	return (res);
}

void	ft_pipefree(t_pipe *pip)
{
	t_pipe	*tmp;

	tmp = pip->next;
	while (tmp)
	{
		free(pip);
		pip = tmp;
		tmp = pip->next;
	}
	free(pip);
}
