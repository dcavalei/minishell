/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:31:45 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:31:45 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	advance_until_closed_quote(char *str, int i, char quote)
{
	i++;
	while (str[i] != quote)
	{
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

int	get_next_split(char *str)
{
	int		i;

	i = 0;
	if (char_exists(" |&<>", str[i]) == 1)
	{
		if (char_exists("|&<>", str[i]) == 1 && str[i] == str[i + 1])
			return (2);
		return (1);
	}
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			i = advance_until_closed_quote(str, i, '\'');
		else if (str[i] == '"')
			i = advance_until_closed_quote(str, i, '"');
		if (char_exists(" |&<>", str[i]) == 1)
			return (i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (i);
}
