/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:54:56 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:30:18 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	simple_command_prompt(t_simple_command *simple_command)
{
	printf("\t================[ SIMPLE COMMAND ]================\n");
	printf("\tǁ\tnumber_of_arguments = "
		ANSI_F_CYAN"%i"ANSI_RESET"\n",
		simple_command->number_of_arguments);
	printf("\tǁ\tnumber_of_available_arguments = "
		ANSI_F_CYAN"%i"ANSI_RESET"\n",
		simple_command->number_of_available_arguments);
	printf("\tǁ\tsimple_command->input_file = "
		ANSI_F_BYELLOW"%s"ANSI_RESET"\n",
		simple_command->input_file);
	printf("\tǁ\tsimple_command->output_file = "
		ANSI_F_BYELLOW"%s"ANSI_RESET"\n",
		simple_command->output_file);
	printf("\tǁ\tsimple_command->flags = "
		ANSI_F_GREEN"%u"ANSI_RESET"\n",
		simple_command->flags);
	printf("\tǁ\targuments:\n\tǁ\n");
}

void	show_simple_command(t_simple_command *simple_command,
	int show_null_arguments)
{
	int	i;

	simple_command_prompt(simple_command);
	if (!simple_command->number_of_arguments)
	{
		printf("\tǁ\t"ANSI_B_RED"NO ARGUMENTS!"ANSI_RESET"\n");
		return ;
	}
	i = -1;
	while (++i <= simple_command->number_of_available_arguments
		+ simple_command->number_of_arguments)
	{
		if (show_null_arguments
			&& i == simple_command->number_of_available_arguments
			+ simple_command->number_of_arguments)
			printf("\tǁ\t[%i] "ANSI_B_BBLUE"%s"ANSI_RESET
				" must be (null)\n",
				i, simple_command->arguments[i]);
		else if (simple_command->arguments[i]
			|| (simple_command->arguments[i] == NULL
				&& show_null_arguments))
			printf("\tǁ\t[%i] "ANSI_B_BBLUE"%s"ANSI_RESET"\n",
				i, simple_command->arguments[i]);
	}
}

static void	print_header( void )
{
	printf(" #############################################################\n");
	printf("# ======================= [ COMMAND ] ======================= #\n");
	printf(" #############################################################\n");
}

void	show_command(t_command *command,
	int show_null_arguments)
{
	int	i;

	print_header();
	printf("    CREATE "ANSI_F_GREEN"128"ANSI_RESET
		" | APPEND "ANSI_F_GREEN"64"ANSI_RESET
		" | INPUT_FILE "ANSI_F_GREEN"32"ANSI_RESET
		" | INPUT_STDIN "ANSI_F_GREEN"16"ANSI_RESET"\n\n");
	printf("\tnumber_of_simple_commands = "ANSI_F_CYAN"%i"ANSI_RESET"\n",
		command->number_of_simple_commands);
	printf("\tnumber_of_available_simple_commands = "
		ANSI_F_CYAN"%i"ANSI_RESET"\n",
		command->number_of_available_simple_commands);
	printf("\tcurrent_simple_command = "ANSI_F_CYAN"%i"ANSI_RESET"\n",
		command->current_simple_command);
	printf("\tsimple commands:\n\n");
	if (!command->number_of_simple_commands
		&& printf("\t"ANSI_B_RED"NO SIMPLE COMMANDS!"ANSI_RESET"\n"))
		return ;
	i = -1;
	while (++i < command->number_of_simple_commands)
		show_simple_command(command->simple_commands[i], show_null_arguments);
	printf(" #############################################################\n");
	printf("# ========================= [ END ] ========================= #\n");
	printf(" #############################################################\n\n");
}
