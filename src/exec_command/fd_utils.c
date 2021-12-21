/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:30:50 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:30:50 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_original_fd(t_data *d)
{
	d->cmd->original_fdin = dup(STDIN_FILENO);
	d->cmd->original_fdout = dup(STDOUT_FILENO);
}

void	restore_and_close_file_descritors(t_data *d)
{
	dup2(d->cmd->original_fdin, STDIN_FILENO);
	dup2(d->cmd->original_fdout, STDOUT_FILENO);
	close(d->cmd->original_fdin);
	close(d->cmd->original_fdout);
}

int	set_fdin(t_command *cmd, int current_cmd)
{
	int	fdin;

	if (cmd->number_of_simple_commands != 0
		&& cmd->simple_commands[current_cmd]->input_file != NULL)
		fdin = open(cmd->simple_commands[current_cmd]->input_file, O_RDONLY);
	else
		fdin = dup(cmd->original_fdin);
	return (fdin);
}

int	set_fdout(t_command *cmd, int current_cmd)
{
	int	fdout;
	int	flags;

	if (cmd->simple_commands[current_cmd]->flags & APPEND)
		flags = O_WRONLY | O_APPEND;
	else
		flags = O_WRONLY | O_TRUNC;
	if (cmd->number_of_simple_commands != 0
		&& cmd->simple_commands[current_cmd]->output_file != NULL)
		fdout = open(cmd->simple_commands[current_cmd]->output_file, flags);
	else
		fdout = dup(cmd->original_fdout);
	return (fdout);
}
