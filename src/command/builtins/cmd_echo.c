/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:45:20 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:09:52 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns a string with the name of the env variable
// needs to receive input started by a '$' char.
int	cmd_echo(t_data *data)
{
	t_simple_command	*simple_command;
	int					off_set;
	int					i;

	simple_command = get_current_simple_command(data->cmd);
	data->cmd->current_simple_command++;
	off_set = (simple_command->number_of_arguments > 1
			&& !ft_strcmp(simple_command->arguments[1], "-n"));
	i = off_set;
	while (++i < simple_command->number_of_arguments)
	{
		printf("%s", simple_command->arguments[i]);
		if (i % (simple_command->number_of_arguments - 1))
			printf(" ");
	}
	if (!off_set)
		printf("\n");
	return ((errno = 0));
}
