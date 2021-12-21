/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:18:20 by dcavalei          #+#    #+#             */
/*   Updated: 2021/09/16 14:18:22 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(t_data *data, t_simple_command *simple_command,
	int *valid_index)
{
	int					i;
	int					j;
	int					len;

	j = -1;
	while (++j < data->env.number_of_variables)
	{
		len = ft_strchr(data->env.env[j], '=') - data->env.env[j];
		i = -1;
		while (valid_index[++i])
		{
			if (!ft_strncmp(data->env.env[j],
					simple_command->arguments[valid_index[i]], len)
				&& data->env.env[j][len] == '=')
			{
				substitute_env(&(data->env), NULL, j--);
				break ;
			}
		}
	}
}

int	substitute_env(t_env *env, char *str, int index)
{
	free(env->env[index]);
	if (str)
	{
		env->env[index] = ft_strdup(str);
		if (!(env->env[index]))
			return (errno);
		return (0);
	}
	env->number_of_available_variables++;
	env->number_of_variables--;
	while (index <= env->number_of_variables)
	{
		env->env[index] = env->env[index + 1];
		index++;
	}
	return (0);
}

int	cmd_unset(t_data *data)
{
	t_simple_command	*simple_command;
	int					*valid_index;

	simple_command = get_current_simple_command(data->cmd);
	data->cmd->current_simple_command++;
	valid_index = get_valid_name_index_array(simple_command);
	if (!valid_index)
	{
		print_error("minishell", "unset", NULL, "errno");
		return (errno);
	}
	remove_env(data, simple_command, valid_index);
	free(valid_index);
	return (0);
}
