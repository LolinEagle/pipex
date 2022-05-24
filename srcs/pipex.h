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

typedef struct s_pipe
{
	int				pipe[2];
	int				ac;
	struct s_pipe	*next;
}					t_pipe;

// struct.c		5 functions
t_cmd	*ft_init_cmd(int ac, char **av);
t_pipe	*ft_init_pipe(int ac);
t_pipe	*ft_pipenew(int ac);
void	ft_pipefree(t_pipe *pip);

// ft_main.c	4 functions
void	ft_close(int fd1, int fd2);
void	ft_close_main(int fd[2]);
void	ft_close_pipe(t_pipe *pip);
void	ft_free_split(char **str);

// command.c	2 functions
t_cmd	*ft_cmdnew(char *cmd);
void	ft_cmdfree(t_cmd *cmd);

// ft_pipex.c	5 functions
void	ft_strtolower(char *s);
void	ft_perror(char *str);
void	ft_perror_cmd(char *str);
char	*ft_is_path(char *aenv);
char	**ft_find_paths(char **aenv);

// child.c		5 functions
void	ft_pipex_child(char **cmd, char **aenv);
void	ft_free_child(int fd[2], int end[2], t_cmd *cmd);
void	pipex_child0(int fd[2], int end[2], t_cmd *cmd, char **aenv);
void	pipex_child(int fd[2], int end[2], t_cmd *cmd, char **aenv);
void	pipex_child1(int fd[2], int end[2], t_cmd *cmd, char **aenv);

// pipex.c		2 functions
void	pipex(int fd[2], t_cmd *pipex, int ac, char **aenv);

// main.c		5 functions

#endif
