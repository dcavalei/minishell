/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:45:38 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:45:40 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**realloc_wc(int wc, char **res)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (wc + 1));
	if (!temp)
		return (NULL);
	i = 0;
	if (wc > 0)
	{
		while (i < wc)
		{
			temp[i] = res[i];
			i++;
		}
		free(res);
	}
	temp[i] = NULL;
	return (temp);
}

int	split_words(char *str, char ***res)
{
	int	i;
	int	size_next_word;
	int	wc;

	i = ignore_spaces(str, 0);
	wc = 0;
	while (str[i] != '\0')
	{
		size_next_word = get_next_split(&str[i]);
		if (size_next_word == -1)
			return (-1);
		(*res)[wc] = saveword(&str[i], size_next_word);
		wc++;
		*res = realloc_wc(wc, *res);
		i += size_next_word;
		i = ignore_spaces(str, i);
	}
	return (wc);
}

char	**ft_parser(char *str)
{
	char		**res;

	if (!str || !*str)
		return (NULL);
	res = realloc_wc(0, NULL);
	if (split_words(str, &res) == -1)
	{
		ft_free_array_array(res);
		ft_putstr(ANSI_F_BRED);
		ft_putstr("ERROR UNCLOSED QUOTES\n");
		ft_putstr(ANSI_RESET);
		return (NULL);
	}
	return (res);
}
