/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:45:12 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 11:45:13 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hearbeat(t_data *data, int i)
{
	char	*error_num;

	error_num = ft_itoa(errno);
	if (errno != 0)
		i += ft_strlcat(data->prompt + i, ANSI_F_BRED " [", PROMPT_MAX - i);
	else
		i += ft_strlcat(data->prompt + i, ANSI_F_BGREEN " [", PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, error_num, PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, "]" ANSI_RESET, PROMPT_MAX - i);
	free(error_num);
	return (i);
}

int	put_pwd_prompt(t_data *data, char *pwd, int i)
{
	int	home_len;

	home_len = 0;
	i += ft_strlcat(data->prompt + i, ANSI_F_CYAN, PROMPT_MAX - i);
	if (data->home)
	{
		home_len = ft_strlen(data->home);
		if (ft_strncmp(data->home, pwd, home_len) == 0)
		{
			i += ft_strlcat(data->prompt + i, "~", PROMPT_MAX - i);
			i += ft_strlcat(data->prompt + i, pwd + home_len, PROMPT_MAX - i);
		}
		else
			i += ft_strlcat(data->prompt + i, pwd, PROMPT_MAX - i);
	}
	else
		i += ft_strlcat(data->prompt + i, pwd, PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, ANSI_RESET, PROMPT_MAX - i);
	i = hearbeat(data, i);
	i += ft_strlcat(data->prompt + i, "$> ", PROMPT_MAX - i);
	return (i);
}

void	build_prompt(t_data *data)
{
	char			pwd[PATH_MAX];
	int				i;

	getcwd(pwd, PATH_MAX);
	if (!data->home)
		data->home = getenv("HOME");
	if (!data->user)
		data->user = getenv("USER");
	i = -1;
	while (data->prompt[++i])
		data->prompt[i] = 0;
	i = ft_strlcat(data->prompt, ANSI_F_GREEN, PROMPT_MAX);
	if (data->user)
		i += ft_strlcat(data->prompt + i, data->user, PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, ANSI_RESET, PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, "@", PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, ANSI_F_GREEN, PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, "minishell", PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, ANSI_RESET, PROMPT_MAX - i);
	i += ft_strlcat(data->prompt + i, ": ", PROMPT_MAX - i);
	i = put_pwd_prompt(data, pwd, i);
}
