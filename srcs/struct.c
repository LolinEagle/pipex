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
	i = 3;
	while (i < ac - 4)
	{
		tmp->next = ft_cmdnew(av[i]);
		if (!tmp->next)
			return (ft_cmd_return(cmd));
		tmp = tmp->next;
		i++;
	}
	return (cmd);
}
