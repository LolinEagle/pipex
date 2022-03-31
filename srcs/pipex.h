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

// pipex.c  1 functions
void	pipex(void);

// main.c   1 functions

#endif