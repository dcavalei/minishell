/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:52:44 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 11:58:04 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_simple_command(t_simple_command *simple_command)
{
	int	i;

	i = -1;
	while (++i < simple_command->number_of_arguments)
		free(simple_command->arguments[i]);
	free(simple_command->arguments);
	free(simple_command->input_file);
	free(simple_command->output_file);
	free(simple_command);
}

void	destroy_command(t_command *command)
{
	int	i;

	i = -1;
	while (++i < command->number_of_simple_commands)
		destroy_simple_command(command->simple_commands[i]);
	free(command->simple_commands);
	free(command);
}

t_simple_command	*get_current_simple_command(t_command *command)
{
	return (command->simple_commands[command->current_simple_command]);
}

int	insert_argument(t_simple_command *simple_command, char *argument)
{
	if (!simple_command || !argument)
		return (0);
	if (simple_command->number_of_available_arguments == 0)
	{
		if (!malloc_arguments(simple_command))
			return (0);
	}
	if (simple_command->number_of_available_arguments != 0)
	{
		simple_command->arguments[simple_command->number_of_arguments]
			= ft_strdup(argument);
		simple_command->number_of_arguments++;
		simple_command->number_of_available_arguments--;
	}
	return (1);
}

int	insert_simple_command(t_command *command,
	t_simple_command *simple_command)
{
	if (!command || !simple_command)
		return (0);
	if (command->number_of_available_simple_commands == 0)
	{
		if (!malloc_simple_commands(command))
			return (0);
	}
	if (command->number_of_available_simple_commands != 0)
	{
		command->simple_commands[command->number_of_simple_commands]
			= simple_command;
		command->number_of_simple_commands++;
		command->number_of_available_simple_commands--;
	}
	return (1);
}
