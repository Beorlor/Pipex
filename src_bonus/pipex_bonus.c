/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:05:17 by jedurand          #+#    #+#             */
/*   Updated: 2024/01/12 17:12:05 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Main function of the pipex program.
 * It sets up the environment for the pipe and executes the commands provided.
 * Supports 'here_doc' functionality for additional input handling.
 */
int	main(int ac, char **av, char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;

	if (ac < 5)
		exit_handler(1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (ac < 6)
			exit_handler(1);
		i = 3;
		fd_out = open_file(av[ac - 1], 2);
		here_doc(av);
	}
	else
	{
		i = 2;
		fd_in = open_file(av[1], 0);
		fd_out = open_file(av[ac - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < ac - 2)
		do_pipe(av[i++], env);
	dup2(fd_out, 1);
	exec(av[ac - 2], env);
}

/**
 * Sets up a pipe and forks the process.
 * The child process executes a command,
 * and the parent process sets up for the next command.
 */
void	do_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

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
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

/**
 * Executes a command using execve.
 * It splits the command into arguments, finds the path, and then executes it.
 * Prints an error message and exits if the command is not found.
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

/**
 * Handles the 'here_doc' functionality.
 * Creates a pipe, forks the process,
 * and reads input until the delimiter is found.
 */
void	here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

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
		here_doc_put_in(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

/**
 * Part of the 'here_doc' functionality.
 * This function is executed by the child process
 * to read input and write to a pipe.
 */
void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}
