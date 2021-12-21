/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:45:49 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:45:49 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	char_exists(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)(c);
	while (i <= ft_strlen(s))
	{
		if (s[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

int	ignore_spaces(char *str, int i)
{
	while (str[i] == ' ')
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

void	ft_print_split(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		printf(ANSI_F_BCYAN "%d.[" ANSI_RESET, i);
		printf("%s" ANSI_F_BCYAN "]" ANSI_RESET "\n", res[i]);
		i++;
	}
}
