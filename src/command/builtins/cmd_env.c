/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:45:59 by dcavalei          #+#    #+#             */
/*   Updated: 2021/09/16 13:46:12 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_data *data)
{
	t_simple_command	*simple_command;
	int					i;

	simple_command = get_current_simple_command(data->cmd);
	data->cmd->current_simple_command++;
	if (simple_command->number_of_arguments > 1)
	{
		print_error("minishell", "env", "not implemented",
			"too many arguments");
		return ((errno = 1));
	}
	i = -1;
	while (++i < data->env.number_of_variables)
		printf("%s\n", data->env.env[i]);
	return ((errno = 0));
}

char	*my_get_env(t_env env, char *name)
{
	int	i;
	int	len;

	if (!name || !(*name))
		return (NULL);
	i = -1;
	len = ft_strlen(name);
	while (env.env[++i])
	{
		if (!ft_strncmp(env.env[i], name, len) && env.env[i][len] == '=')
			return (&env.env[i][len] + 1);
	}
	return (NULL);
}
