/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmartins <rmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:52:13 by dcavalei          #+#    #+#             */
/*   Updated: 2021/08/20 19:47:05 by rmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_data *data, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &print_newline);
	ft_bzero(data, sizeof(t_data));
	if (set_up_env(data, env))
		return (1);
	return (0);
}

int	set_up_env(t_data *data, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (data->env.number_of_available_variables == 0
			&& realloc_env(&(data->env)))
			return (1);
		data->env.env[i] = ft_strdup(env[i]);
		data->env.number_of_available_variables--;
		data->env.number_of_variables++;
	}
	return (0);
}

int	realloc_env(t_env *env)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *)
			* (env->number_of_variables + ENV_REALLOC_SIZE + 1));
	if (!new_env)
		return (1);
	new_env[env->number_of_variables + ENV_REALLOC_SIZE] = NULL;
	env->number_of_available_variables = ENV_REALLOC_SIZE;
	i = -1;
	while (++i < env->number_of_variables)
		new_env[i] = env->env[i];
	ft_bzero(new_env + i, sizeof(char *) * (ENV_REALLOC_SIZE));
	free(env->env);
	env->env = new_env;
	return (0);
}

void	free_env(t_env env)
{
	int	i;

	i = -1;
	while (++i < env.number_of_variables)
		free(env.env[i]);
	free(env.env);
}
