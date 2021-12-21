/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 21:15:17 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:10:12 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd(t_data *data)
{
	t_simple_command	*simple_command;

	simple_command = get_current_simple_command(data->cmd);
	data->cmd->current_simple_command++;
	if (simple_command->number_of_arguments == 1
		|| ft_strcmp(simple_command->arguments[1], "~") == 0)
	{
		if (cmd_cd_tilde(data, simple_command))
			return (errno);
	}
	else if (ft_strncmp(simple_command->arguments[1], "~/", 2) == 0)
	{
		if (cmd_cd_home_relative_path(data, simple_command))
			return (errno);
	}
	else if (ft_strcmp(simple_command->arguments[1], "-") == 0)
	{
		if (cmd_cd_minus(data))
			return (errno);
	}
	else if (cmd_cd_default(data, simple_command))
		return (errno);
	return ((errno = 0));
}

int	get_env_index(t_env env, char *str)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (++i < env.number_of_variables)
	{
		if (!ft_strncmp(env.env[i], str, len))
			return (i);
	}
	return (-1);
}

void	pwd_oldpwd_handler(t_data *data)
{
	int		pwd_i;
	int		oldpwd_i;
	char	*tmp;
	char	ptr[PATH_MAX];

	pwd_i = get_env_index(data->env, "PWD=");
	oldpwd_i = get_env_index(data->env, "OLDPWD=");
	if (oldpwd_i != -1)
	{
		if (pwd_i != -1)
		{
			tmp = ft_strjoin("OLDPWD=", my_get_env(data->env, "PWD"));
			substitute_env(&data->env, tmp, oldpwd_i);
			free (tmp);
		}
	}
	if (pwd_i != -1)
	{
		tmp = ft_strjoin("PWD=", getcwd(ptr, PATH_MAX));
		substitute_env(&data->env, tmp, pwd_i);
		free (tmp);
	}
}
