/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:48:24 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:19:06 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	overwrite_handler(t_data *data,
	t_simple_command *simple_command, int *i)
{
	if (is_special_input(data->res[++(*i)]))
		return ((errno = print_error("minishell", NULL,
					"syntax error near unexpected token", data->res[(*i)])));
	parse_str(data, &data->res[(*i)]);
	if (close(open(data->res[(*i)], O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
	{
		print_error("minishell", NULL, data->res[(*i)++], "errno");
		return (errno);
	}
	if (simple_command->flags & APPEND)
		simple_command->flags ^= APPEND;
	simple_command->flags |= CREATE;
	free(simple_command->output_file);
	simple_command->output_file = ft_strdup(data->res[(*i)++]);
	return (0);
}

int	append_handler(t_data *data,
	t_simple_command *simple_command, int *i)
{
	if (is_special_input(data->res[++(*i)]))
		return ((errno = print_error("minishell", NULL,
					"syntax error near unexpected token", data->res[(*i)])));
	parse_str(data, &data->res[(*i)]);
	if (close(open(data->res[(*i)], O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
	{
		print_error("minishell", NULL, data->res[(*i)++], "errno");
		return (errno);
	}
	if (simple_command->flags & CREATE)
		simple_command->flags ^= CREATE;
	simple_command->flags |= APPEND;
	free(simple_command->output_file);
	simple_command->output_file = ft_strdup(data->res[(*i)++]);
	return (0);
}

int	redir_handler(t_data *data,
	t_simple_command *simple_command, int *i)
{
	if (is_special_input(data->res[++(*i)]))
		return ((errno = print_error("minishell", NULL,
					"syntax error near unexpected token", data->res[(*i)])));
	parse_str(data, &data->res[(*i)]);
	if (close(open(data->res[(*i)], O_RDONLY)))
	{
		errno = 2;
		print_error("minishell", NULL, data->res[(*i)++], "errno");
		return (errno);
	}
	if (simple_command->flags & INPUT_STDIN)
		simple_command->flags ^= INPUT_STDIN;
	simple_command->flags |= INPUT_FILE;
	free(simple_command->input_file);
	simple_command->input_file = ft_strdup(data->res[(*i)++]);
	return (0);
}

static void	get_user_input(t_data *data, int fd, int i)
{
	char	*tmp;

	tmp = readline("> ");
	if (!tmp)
	{
		print_error("minishell", "warning",
			"delimited by end-of-file, expecting", data->res[i]);
		return ;
	}
	parse_str(data, &tmp);
	while (ft_strcmp(data->res[i], tmp))
	{
		ft_putstr_fd(tmp, fd);
		ft_putchar_fd('\n', fd);
		free(tmp);
		tmp = readline("> ");
		if (!tmp)
		{
			print_error("minishell", "warning",
				"delimited by end-of-file, expecting", data->res[i]);
			return ;
		}
		parse_str(data, &tmp);
	}
	free(tmp);
}

int	stdin_redir_handler(t_data *data,
	t_simple_command *simple_command, int *i)
{
	int		fd;

	if (is_special_input(data->res[++(*i)]))
		return ((errno = print_error("minishell", NULL,
					"syntax error near unexpected token", data->res[(*i)])));
	parse_str(data, &data->res[(*i)]);
	if (simple_command->flags & INPUT_FILE)
		simple_command->flags ^= INPUT_FILE;
	simple_command->flags |= INPUT_STDIN;
	free(simple_command->input_file);
	simple_command->input_file = ft_strdup(TMP_STDIN_PATH);
	fd = open(TMP_STDIN_PATH, O_CREAT | O_TRUNC | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		(*i)++;
		return ((errno = print_error("minishell", "warning",
					"failed to create file", TMP_STDIN_PATH)));
	}
	get_user_input(data, fd, *i);
	close(fd);
	(*i)++;
	return (0);
}
