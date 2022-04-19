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
# include <errno.h>
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

// ft_main.c	5 functions
void	ft_strtolower(char *s);
void	ft_perror(char *str);
void	ft_free_split(char **str);
t_cmd	*ft_cmdnew(char *cmd);
void	ft_cmdfree(t_cmd *cmd);

// ft_pipex.c	2 functions
char	*ft_is_path(char *aenv);
char	**ft_find_paths(char **aenv);

// pipex.c		4 functions
void	pipex(int fd[2], t_cmd *pipex, char **aenv);

// main.c		4 functions

#endif
