/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:26:58 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:09:40 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	dollar_sign_handler(t_data *data, char *buffer, char *str, t_index *i)
{
	char	*name;
	char	*value;

	if (!data || !buffer || !str || !i || str[(*i).str] != '$')
		return (print_error("minishell", NULL,
				"function", "dollar_sign_handler()"));
	if (str[((*i).str) + 1] == '?')
		return (errno_expansion(buffer, i));
	name = get_name(str, &((*i).str));
	value = NULL;
	if (!name)
		return (print_error("minishell", NULL, "function error", "get_name()"));
	if (!*name)
		((*i).buffer) += ft_strlcpy(buffer + ((*i).buffer),
				"$", PROMPT_MAX - ((*i).buffer));
	else
	{
		value = my_get_env(data->env, name);
		if (value)
			((*i).buffer) += ft_strlcpy(buffer + ((*i).buffer),
					value, PROMPT_MAX - ((*i).buffer));
	}
	free(name);
	return (0);
}

int	double_quote_handler(t_data *data, char *buffer, char *str, t_index *i)
{
	int	unclosed;

	if (!data || !buffer || !str || !i || str[(*i).str] != '"')
		return (print_error("minishell", NULL,
				"function", "double_quote_handler()"));
	unclosed = 1;
	((*i).str)++;
	while (str[(*i).str] && unclosed)
	{
		if (str[(*i).str] == '"')
		{
			unclosed = 0;
			((*i).str)++;
		}
		else if (str[(*i).str] == '$')
		{
			if (dollar_sign_handler(data, buffer, str, i))
				return (1);
		}
		else
			add_char_to_buffer(buffer, str, i);
	}
	if (unclosed)
		print_error("minishell", NULL, "function", "unclosed quotation mark");
	return (unclosed);
}

int	single_quote_handler(t_data *data, char *buffer, char *str, t_index *i)
{
	int	unclosed;

	if (!data || !buffer || !str || !i || str[(*i).str] != '\'')
		return (print_error("minishell", NULL,
				"function", "single_quote_handler()"));
	unclosed = 1;
	((*i).str)++;
	while (str[(*i).str] && unclosed)
	{
		if (str[(*i).str] == '\'')
		{
			unclosed = 0;
			((*i).str)++;
		}
		else
			add_char_to_buffer(buffer, str, i);
	}
	if (unclosed)
		print_error("minishell", NULL, "function", "unclosed quotation mark");
	return (unclosed);
}

static int	swap_buffer(char *buffer, char **str, t_index i)
{
	buffer[i.buffer] = 0;
	free(*str);
	*str = ft_strdup(buffer);
	return (0);
}

int	parse_str(t_data *data, char **str)
{
	char	buffer[PROMPT_MAX];
	t_index	i;

	ft_bzero(&i, sizeof(i));
	while ((*str)[i.str])
	{
		if ((*str)[i.str] == '$')
		{
			if (dollar_sign_handler(data, buffer, *str, &i))
				return (1);
		}
		else if ((*str)[i.str] == '"')
		{
			if (double_quote_handler(data, buffer, *str, &i))
				return (1);
		}
		else if ((*str)[i.str] == '\'')
		{
			if (single_quote_handler(data, buffer, *str, &i))
				return (1);
		}
		else
			add_char_to_buffer(buffer, *str, &i);
	}
	return (swap_buffer(buffer, str, i));
}
