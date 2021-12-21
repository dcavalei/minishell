/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:17:15 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:01:55 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	*get_name(char *str, int *i)
{
	char	name[PROMPT_MAX];
	int		j;

	if (!str || str[*i] != '$')
		return (NULL);
	(*i)++;
	j = 0;
	if (ft_isalpha(str[*i]) || str[*i] == '_')
		name[j++] = str[*i];
	else
		return (ft_strdup(""));
	(*i)++;
	while (str[*i])
	{
		if (ft_isalnum(str[*i]) || str[*i] == '_')
			name[j++] = str[*i];
		else
			break ;
		(*i)++;
	}
	name[j] = 0;
	return (ft_strdup(name));
}

int	errno_expansion(char *buffer, t_index *i)
{
	char	*value;

	value = ft_itoa(errno);
	((*i).str) += 2;
	((*i).buffer) += ft_strlcpy(buffer + ((*i).buffer),
			value, PROMPT_MAX - ((*i).buffer));
	free(value);
	return (0);
}

void	add_char_to_buffer(char *buffer, char *str,	t_index *i)
{
	if (PATH_MAX - ((*i).str) > 1)
	{
		buffer[(*i).buffer] = str[(*i).str];
		((*i).buffer)++;
		((*i).str)++;
	}
}

void	parse_simple_command_args(t_data *data)
{
	t_simple_command	*simple_command;
	int					i;

	simple_command = get_current_simple_command(data->cmd);
	i = -1;
	while (simple_command->arguments[++i])
		parse_str(data, &simple_command->arguments[i]);
}
