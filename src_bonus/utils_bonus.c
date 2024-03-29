/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:05:06 by jedurand          #+#    #+#             */
/*   Updated: 2024/02/16 18:05:31 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Handles the exit procedure of the program.
 * Prints a usage message if the exit code indicates a usage error.
 */
void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("Usage: ./pipex infile cmd cmd outfile\n", 2);
	exit(EXIT_FAILURE);
}

/**
 * Opens a file based on the specified mode (read, write, or append).
 * Returns the file descriptor of the opened file.
 * Exits the program using perror to display an error message in case of failure.
 */
int	open_file(char *file, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
		fd = open(file, O_RDONLY);
	else if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (in_or_out == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * Retrieves the absolute path of a command from the PATH environment variable.
 * Returns the path if found, otherwise returns the original command.
 */
char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	return (cmd);
}

/**
 * Custom implementation to get the value of an environment variable.
 * Returns the value of the specified environment variable.
 */
char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

/**
 * Frees a dynamically allocated array of strings (char**).
 */
void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
