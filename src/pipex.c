/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:05:32 by jedurand          #+#    #+#             */
/*   Updated: 2024/01/12 15:05:35 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * The main function that sets up a pipeline between two processes.
 * It creates a pipe and forks the process into a parent and a child.
 * It then calls the respective functions for each process to handle their part of the pipeline.
 */
int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd) == -1)
	{
    	perror("pipe error");
    	exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
   		perror("fork error");
   		exit(EXIT_FAILURE);
	}
	if (!pid)
		child(av, p_fd, env);
	parent(av, p_fd, env);
}

/**
 * Child process function.
 * Opens the input file, redirects stdin to read from this file, and stdout to write to a pipe.
 * It then executes a given command with this setup.
 */
void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

/**
 * Parent process function.
 * Opens the output file, redirects stdin to read from a pipe (output of child), and stdout to write to this file.
 * It then executes a given command with this setup.
 */
void	parent(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], env);
}

/**
 * Executes a command.
 * Splits the command into arguments, finds the path of the command, and executes it using execve.
 * In case of an error, prints the error and exits.
 */
void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		perror("execve error");
    	ft_free_tab(s_cmd);
    	exit(EXIT_FAILURE);
	}
}
