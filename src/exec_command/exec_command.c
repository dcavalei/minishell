/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:30:43 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:30:46 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_path(char **paths, char *command)
{
	int			i;
	char		*slash_command;
	char		*full_path;
	struct stat	stat_buffer;

	slash_command = ft_strjoin("/", command);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], slash_command);
		if (stat(full_path, &stat_buffer) == EXIT_SUCCESS)
		{
			errno = 0;
			free(slash_command);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(slash_command);
	return (NULL);
}

char	*get_path(char **env, char *command, int i)
{
	char	**paths;
	char	*full_path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			paths = ft_split(&env[i][5], ':');
			full_path = get_valid_path(paths, command);
			if (full_path != NULL)
			{
				ft_free_array_array(paths);
				return (full_path);
			}
			else
			{
				ft_free_array_array(paths);
				break ;
			}
		}
		i++;
	}
	return (NULL);
}

int	execute_child(int pid, char *full_path, char **commands, char **env)
{
	if (pid < 0)
	{
		print_error(NULL, NULL, NULL, "Cannot fork process\n");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(full_path, commands, env);
		print_error("minishell", full_path, NULL, "errno");
		errno = 127;
		free(full_path);
		exit(errno);
	}
	return (EXIT_SUCCESS);
}

int	execute_command(t_simple_command *cmd, char **env)
{
	char	*full_path;
	int		pid;

	if (cmd->arguments[0][0] == '/')
		full_path = cmd->arguments[0];
	else
		full_path = get_path(env, cmd->arguments[0], 0);
	if (full_path != NULL)
	{
		pid = fork();
		if (execute_child(pid, full_path, cmd->arguments, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		cmd->pid = pid;
		if (cmd->arguments[0][0] != '/')
			free(full_path);
	}
	else
	{
		print_error(NULL, cmd->arguments[0], NULL, "command not found");
		errno = 127;
	}
	return (errno);
}
