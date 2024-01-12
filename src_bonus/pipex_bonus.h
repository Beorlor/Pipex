/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:04:46 by jedurand          #+#    #+#             */
/*   Updated: 2024/01/12 17:12:44 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

// Function prototypes for pipex_bonus.c
int		main(int ac, char **av, char **env);
void	do_pipe(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	here_doc(char **av);
void	here_doc_put_in(char **av, int *p_fd);

// Function prototypes for utils_bonus.c
void	exit_handler(int n_exit);
int		open_file(char *file, int in_or_out);
char	*get_path(char *cmd, char **env);
char	*my_getenv(char *name, char **env);
void	ft_free_tab(char **tab);

#endif
