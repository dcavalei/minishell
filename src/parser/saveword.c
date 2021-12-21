/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveword.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:45:44 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:45:44 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*saveword(const char *str, int size)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
