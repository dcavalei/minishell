/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:24:00 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:45:01 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_command_handler_cont(t_data *data,
	t_simple_command *simple_command, int *i)
{
	if (!ft_strcmp(data->res[*i], "<"))
	{
		if (redir_handler(data, simple_command, i))
			return (errno);
	}
	else if (!ft_strcmp(data->res[*i], "<<"))
	{
		if (stdin_redir_handler(data, simple_command, i))
			return (errno);
	}
	else
	{
		parse_str(data, &data->res[*i]);
		insert_argument(simple_command, data->res[(*i)++]);
	}
	return (0);
}

int	simple_command_handler(t_data *data,
	t_simple_command *simple_command, int *i)
{
	int	tmp;

	while (data->res[*i] && ft_strcmp(data->res[*i], "|"))
	{
		if (!ft_strcmp(data->res[*i], ">"))
		{
			if (overwrite_handler(data, simple_command, i))
				return (errno);
		}
		else if (!ft_strcmp(data->res[*i], ">>"))
		{
			if (append_handler(data, simple_command, i))
				return (errno);
		}
		else
		{
			tmp = simple_command_handler_cont(data, simple_command, i);
			if (tmp)
				return (tmp);
		}
	}
	return (0);
}

int	build_command(t_data *data)
{
	t_simple_command	*simple_command;
	int					i;

	i = 0;
	while (data->res[i])
	{
		simple_command = new_simple_command();
		if (!simple_command_handler(data, simple_command, &i)
			&& simple_command->number_of_arguments)
			insert_simple_command(data->cmd, simple_command);
		else
			destroy_simple_command(simple_command);
		if (data->res[i])
			i++;
	}
	return (0);
}

int	is_special_input(char *string)
{
	if (!string)
		return (1);
	return (!(ft_strcmp(string, ">"))
		|| !(ft_strcmp(string, ">>"))
		|| !(ft_strcmp(string, "<"))
		|| !(ft_strcmp(string, "<<"))
		|| !(ft_strcmp(string, "|"))
		|| !(ft_strcmp(string, "||"))
		|| !(ft_strcmp(string, "&"))
		|| !(ft_strcmp(string, "&&"))
		|| !(ft_strcmp(string, ";")));
}
