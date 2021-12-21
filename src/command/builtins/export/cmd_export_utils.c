/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:10:57 by dcavalei          #+#    #+#             */
/*   Updated: 2021/09/16 14:16:48 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check the "name" field from "name=value".
**
**	Allowed syntax:	[a-zA-Z_][a-zA-Z0-9_]*
**
**	Success:		return (0);
**	Error:			return (1);
*/

int	check_name(char *str)
{
	int	i;

	i = 0;
	if (!str || !(ft_isalpha(str[i]) || str[i] == '_'))
		return (1);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	*get_valid_name_index_array(t_simple_command *simple_command)
{
	int	*ptr;
	int	i;
	int	j;
	int	trigger;

	ptr = malloc(sizeof(int) * simple_command->number_of_arguments);
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	trigger = 0;
	while (simple_command->arguments[++i])
	{
		if (check_name(simple_command->arguments[i]) && ++trigger)
			print_error("minishell", simple_command->arguments[0],
				simple_command->arguments[i], "not a valid identifier");
		else
			ptr[j++] = i;
	}
	ptr[j] = 0;
	if (trigger)
		errno = 1;
	else
		errno = 0;
	return (ptr);
}
