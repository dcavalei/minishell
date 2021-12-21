/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:50:56 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:13:07 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_env(t_env *env, char *str)
{
	int	i;

	if (!env)
		return ((errno = 1));
	if (!env->number_of_available_variables)
		realloc_env(env);
	i = env->number_of_variables;
	env->env[i] = ft_strdup(str);
	if (!env->env[i])
		return ((errno = 1));
	env->number_of_available_variables--;
	env->number_of_variables++;
	return (0);
}

static void	set_changed_envs(t_data *data,
	t_simple_command *simp_cmd, int *v_idx, int *r_idx)
{
	int		current_env;
	int		i;
	int		j;
	int		len;
	char	*str;

	current_env = -1;
	j = -1;
	while (++current_env < data->env.number_of_variables)
	{
		str = data->env.env[current_env];
		len = ft_strchr(str, '=') - str;
		i = -1;
		while (v_idx[++i])
		{
			if (!ft_strncmp(str, simp_cmd->arguments[v_idx[i]], len)
				&& str[len] == '=' && simp_cmd->arguments[v_idx[i]][len] == '=')
			{
				r_idx[++j] = v_idx[i];
				substitute_env(&(data->env),
					simp_cmd->arguments[v_idx[i]], current_env);
				break ;
			}
		}
	}
}

static void	set_unchanged_envs(t_data *data,
	t_simple_command *simple_command, int *v_idx, int *r_idx)
{
	int		i;
	int		j;
	int		trigger;
	char	*str;

	i = -1;
	while (v_idx[++i])
	{
		j = -1;
		trigger = 1;
		while (r_idx[++j])
		{
			if (v_idx[i] == r_idx[j] && trigger--)
				break ;
		}
		if (trigger)
		{
			str = simple_command->arguments[v_idx[i]];
			if (!ft_strchr(str, '='))
				continue ;
			if (!data->env.number_of_available_variables)
				realloc_env(&(data->env));
			add_new_env(&(data->env), str);
		}
	}
}

static int	export_one_argument_handler(t_data *data)
{
	int		i;
	int		offset;
	char	*str;

	i = -1;
	while (++i < data->env.number_of_variables)
	{
		str = data->env.env[i];
		offset = ft_strchr(str, '=') - str + 1;
		printf("declare -x %.*s\"%s\"\n", offset, str, str + offset);
	}
	return ((errno = 0));
}

int	cmd_export(t_data *data)
{
	t_simple_command	*simple_command;
	int					*v_idx;
	int					*r_idx;

	simple_command = get_current_simple_command(data->cmd);
	data->cmd->current_simple_command++;
	if (simple_command->number_of_arguments == 1)
		return (export_one_argument_handler(data));
	v_idx = get_valid_name_index_array(simple_command);
	r_idx = malloc(sizeof(int) * (simple_command->number_of_arguments - 1));
	if (!v_idx || !r_idx)
	{
		free(v_idx);
		free(r_idx);
		print_error("minishell", "export", NULL, "errno");
		return (errno);
	}
	ft_bzero(r_idx, simple_command->number_of_arguments * sizeof(int));
	set_changed_envs(data, simple_command, v_idx, r_idx);
	set_unchanged_envs(data, simple_command, v_idx, r_idx);
	free(v_idx);
	free(r_idx);
	return (errno);
}
