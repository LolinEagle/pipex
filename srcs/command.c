/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:34:09 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/24 16:34:12 by frrusso          ###   ########.fr       */
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
	if (!res->cmd)
	{
		free(res);
		return (NULL);
	}
	res->next = NULL;
	return (res);
}

void	ft_cmdfree(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp)
	{
		ft_free_split(cmd->cmd);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	ft_free_split(cmd->cmd);
	free(cmd);
}
