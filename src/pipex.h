/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:05:41 by jedurand          #+#    #+#             */
/*   Updated: 2024/01/12 15:05:44 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

void exec(char *cmd, char **env);
void child(char **av, int *p_fd, char **env);
void parent(char **av, int *p_fd, char **env);
int main(int ac, char **av, char **env);

void exit_handler(int n_exit);
int open_file(char *file, int in_or_out);
void ft_free_tab(char **tab);
char *my_getenv(char *name, char **env);
char *get_path(char *cmd, char **env);

#endif
