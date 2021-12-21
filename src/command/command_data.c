/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:49:54 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 11:58:41 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_command	*new_simple_command(void)
{
	t_simple_command	*simple_command;

	simple_command = malloc(sizeof(t_simple_command));
	if (!simple_command)
		return (NULL);
	ft_bzero(simple_command, sizeof(t_simple_command));
	return (simple_command);
}

t_command	*new_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	ft_bzero(command, sizeof(t_command));
	return (command);
}

int	malloc_arguments(t_simple_command *simple_command)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char *) * (simple_command->number_of_arguments
				+ DEFAULT_ARG_AMOUNT + 1));
	if (!tmp)
		return (0);
	simple_command->number_of_available_arguments
		= DEFAULT_ARG_AMOUNT;
	tmp[simple_command->number_of_arguments
		+ DEFAULT_ARG_AMOUNT] = NULL;
	i = -1;
	while (++i < simple_command->number_of_arguments)
		tmp[i] = simple_command->arguments[i];
	j = i;
	while (j <= DEFAULT_ARG_AMOUNT + i)
		tmp[j++] = NULL;
	free(simple_command->arguments);
	simple_command->arguments = tmp;
	return (1);
}

int	malloc_simple_commands(t_command *command)
{
	t_simple_command	**tmp;
	int					i;
	int					j;

	tmp = malloc(sizeof(t_simple_command *)
			* (command->number_of_simple_commands + DEFAULT_ARG_AMOUNT + 1));
	if (!tmp)
		return (0);
	tmp[command->number_of_simple_commands + DEFAULT_ARG_AMOUNT] = NULL;
	command->number_of_available_simple_commands = DEFAULT_ARG_AMOUNT;
	i = -1;
	while (++i < command->number_of_simple_commands)
		tmp[i] = command->simple_commands[i];
	j = i;
	while (j <= DEFAULT_ARG_AMOUNT + i)
		tmp[j++] = NULL;
	free(command->simple_commands);
	command->simple_commands = tmp;
	return (1);
}
