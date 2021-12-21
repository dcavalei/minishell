/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:44:28 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:07:20 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_index
{
	int	str;
	int	buffer;
}			t_index;

int		char_exists(const char *s, int c);
int		ignore_spaces(char *str, int i);
void	ft_print_split(char **res);

int		get_next_split(char *str);
char	*saveword(const char *str, int size);

char	*get_name(char *str, int *i);
int		errno_expansion(char *buffer, t_index *i);
void	add_char_to_buffer(char *buffer, char *str,	t_index *i);
void	parse_simple_command_args(t_data *data);

#endif
