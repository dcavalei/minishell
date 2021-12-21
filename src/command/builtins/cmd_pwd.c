/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:27:45 by dcavalei          #+#    #+#             */
/*   Updated: 2021/09/16 14:18:03 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(t_data *data)
{
	t_simple_command	*simple_command;
	char				temp[PATH_MAX];
	char				*ptr;

	simple_command = get_current_simple_command(data->cmd);
	data->cmd->current_simple_command++;
	if (simple_command->number_of_arguments > 1)
	{
		if (simple_command->arguments[1][0] == '-')
			print_error("minishell", "pwd", "option", "not implemented");
		else
			print_error("minishell", "pwd", NULL, "too many arguments");
		return ((errno = 1));
	}
	ptr = getcwd(temp, PATH_MAX);
	if (!ptr)
	{
		print_error("minishell", "pwd", NULL, "errno");
		return (errno);
	}
	printf("%s\n", ptr);
	return (0);
}
