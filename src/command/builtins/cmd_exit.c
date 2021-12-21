/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:46:58 by dcavalei          #+#    #+#             */
/*   Updated: 2021/09/16 13:48:24 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_checking(t_data *data, t_simple_command *simple_command)
{
	int	i;

	if (simple_command->arguments[1][0] == 0)
	{
		print_error("minishell", "exit", simple_command->arguments[1],
			"numeric argument required");
		return ((errno = 1));
	}
	i = -1;
	while (simple_command->arguments[1][++i])
	{
		if (!ft_isdigit(simple_command->arguments[1][i]))
		{
			print_error("minishell", "exit", simple_command->arguments[1],
				"numeric argument required");
			return ((errno = 1));
		}
	}
	data->exit = 1;
	return ((errno = ft_atoi(simple_command->arguments[1])));
}

int	cmd_exit(t_data *data)
{
	t_simple_command	*simple_command;

	simple_command = get_current_simple_command(data->cmd);
	data->cmd->current_simple_command++;
	printf("exit\n");
	if (simple_command->number_of_arguments == 1)
		data->exit = 1;
	else if (simple_command->number_of_arguments == 2)
		error_checking(data, simple_command);
	else
	{
		print_error("minishell", "exit", NULL, "too many arguments");
		return ((errno = 1));
	}
	return (errno);
}
