/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:44:51 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/18 14:45:13 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_d;

//	don't ask me why but for some reason readline
//	changes errno value to 2 every time it's called
void	fixed_readline_errno(char **input, char *prompt)
{
	int	old_errno;

	old_errno = errno;
	*input = readline(prompt);
	errno = old_errno;
}

// ctrl-c
void	print_newline(int signal_num)
{
	(void)signal_num;
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(g_d.prompt, 1);
}

void	build_run_command(t_data *d)
{
	d->cmd = new_command();
	if (!build_command(d))
	{
		run_commands(d, d->cmd->number_of_simple_commands);
		destroy_command(d->cmd);
		free(d->input);
		ft_free_array_array(d->res);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	init_data(&g_d, env);
	while (g_d.exit != 1)
	{
		build_prompt(&g_d);
		fixed_readline_errno(&(g_d.input), g_d.prompt);
		if (!g_d.input)
		{
			printf("exit");
			break ;
		}
		if (*g_d.input)
			add_history (g_d.input);
		g_d.res = ft_parser(g_d.input);
		if (g_d.res == NULL)
		{
			free(g_d.input);
			continue ;
		}
		build_run_command(&g_d);
	}
	free_env(g_d.env);
	return (errno);
}
