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

int	main(int ac, char **av)
{
	if (ac > 4)
	{
		if (ac > 5)
			write(1, "Usage : ./pipex file1 cmd1 cmd2 file2\n", 38);
		ft_printf("< %s %s | %s > %s\n", av[1], av[2], av[3], av[4]);
	}
	else
		return (write(1, "Usage : ./pipex file1 cmd1 cmd2 file2\n", 38));
	return (0);
}
