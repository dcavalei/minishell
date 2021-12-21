/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:31:07 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:31:30 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_command(t_data *d)
{
	char	**arguments;

	d->i = d->cmd->current_simple_command;
	arguments = d->cmd->simple_commands[d->i]->arguments;
	if (!ft_strcmp(arguments[0], "exit"))
		cmd_exit(d);
	else if (!ft_strcmp(arguments[0], "cd"))
		cmd_cd(d);
	else if (!ft_strcmp(arguments[0], "echo"))
		cmd_echo(d);
	else if (!ft_strcmp(arguments[0], "export"))
		cmd_export(d);
	else if (!ft_strcmp(arguments[0], "pwd"))
		cmd_pwd(d);
	else if (!ft_strcmp(arguments[0], "env"))
		cmd_env(d);
	else if (!ft_strcmp(arguments[0], "unset"))
		cmd_unset(d);
	else
	{
		execute_command(d->cmd->simple_commands[d->i], d->env.env);
		d->cmd->current_simple_command++;
	}
}

int	errno_handler(int wstatus)
{
	int		statuscode;

	statuscode = 0;
	if (WIFEXITED(wstatus))
	{
		statuscode = WEXITSTATUS(wstatus);
	}
	return (statuscode);
}

void	wait_commands(t_command *cmd, t_data *d)
{
	int	wstatus;
	int	i;
	int	tmp_errno;

	i = 0;
	tmp_errno = errno;
	while (i < cmd->number_of_simple_commands)
	{
		waitpid(cmd->simple_commands[i]->pid, &wstatus, 0);
		i++;
	}
	errno = errno_handler(wstatus);
	if (tmp_errno != 0 || d->exit == 1)
		errno = tmp_errno;
}

void	run_commands(t_data *d, int n)
{
	int	fdin;
	int	fdout;
	int	fdpipe[2];

	save_original_fd(d);
	fdin = set_fdin(d->cmd, d->cmd->current_simple_command);
	while (d->cmd->current_simple_command < n && !d->exit)
	{
		d->i = d->cmd->current_simple_command;
		dup2(fdin, 0);
		close(fdin);
		if (d->i == n - 1 || d->cmd->simple_commands[d->i]->output_file != NULL)
			fdout = set_fdout(d->cmd, d->cmd->current_simple_command);
		else
		{
			pipe(fdpipe);
			fdout = fdpipe[STDOUT_FILENO];
			fdin = fdpipe[STDIN_FILENO];
		}
		dup2(fdout, 1);
		close(fdout);
		call_command(d);
	}
	restore_and_close_file_descritors(d);
	wait_commands(d->cmd, d);
}
