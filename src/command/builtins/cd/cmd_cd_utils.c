/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:41:36 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:10:27 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_cd_tilde(t_data *data, t_simple_command *simple_command)
{
	if (data->home)
	{
		free(simple_command->arguments[1]);
		simple_command->arguments[1] = ft_strdup(data->home);
	}
	if (chdir(data->home))
	{
		print_error("minishell", "cd", NULL, "HOME not set");
		return ((errno = 1));
	}
	else
		pwd_oldpwd_handler(data);
	return (0);
}

int	cmd_cd_home_relative_path(t_data *data, t_simple_command *simple_command)
{
	char	*tmp;

	if (!data->home)
	{
		print_error("minishell", "cd", NULL, "HOME not set");
		return ((errno = 1));
	}
	tmp = ft_strjoin(data->home, simple_command->arguments[1] + 1);
	free(simple_command->arguments[1]);
	simple_command->arguments[1] = tmp;
	if (chdir(simple_command->arguments[1]))
	{
		print_error("minishell", "cd", simple_command->arguments[1], "errno");
		return (errno);
	}
	else
		pwd_oldpwd_handler(data);
	return (0);
}

int	cmd_cd_minus(t_data *data)
{
	char	*tmp;
	int		i;

	i = get_env_index(data->env, "OLDPWD=");
	tmp = NULL;
	if (i != -1)
		tmp = ft_strchr(data->env.env[i], '=') + 1;
	if (!tmp)
	{
		print_error("minishell", "cd", NULL, "OLDPWD not set");
		return ((errno = 1));
	}
	else if (chdir(tmp))
	{
		print_error("minishell", "cd", tmp, "errno");
		return (errno);
	}
	else
		pwd_oldpwd_handler(data);
	return (0);
}

int	cmd_cd_default(t_data *data, t_simple_command *simple_command)
{
	if (chdir(simple_command->arguments[1]))
	{
		print_error("minishell", "cd", simple_command->arguments[1], "errno");
		return (errno);
	}
	else
		pwd_oldpwd_handler(data);
	return (0);
}
