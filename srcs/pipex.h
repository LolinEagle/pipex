/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:22:58 by frrusso           #+#    #+#             */
/*   Updated: 2022/03/31 12:23:00 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>// open
# include <stdio.h>// perror
# include <string.h>// strerror
# include <sys/wait.h>// wait waitpid
// UNISTD access dup dup2 execve fork pipe unlink

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}					t_cmd;

// ft_main.c	4 functions
void	ft_free_split(char **str);
void	ft_cmd_err(char *cmd);
t_cmd	*ft_cmdnew(char *cmd);
void	ft_cmdfree(t_cmd *cmd);

// pipex.c		5 functions
void	pipex(int fd[2], t_cmd *pipex, char **aenv);

// main.c		4 functions

#endif
