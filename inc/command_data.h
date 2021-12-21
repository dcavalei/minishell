/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_data.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:24:40 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/11 13:24:45 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_DATA_H
# define COMMAND_DATA_H

# define DEFAULT_ARG_AMOUNT 32
# define CREATE 0b10000000
# define APPEND 0b01000000
# define INPUT_FILE 0b00100000
# define INPUT_STDIN 0b00010000

typedef struct s_simple_command
{
	int				number_of_available_arguments;
	int				number_of_arguments;
	char			*input_file;
	char			*output_file;
	unsigned char	flags;
	char			**arguments;
	int				pid;
}				t_simple_command;

typedef struct s_command
{
	int						number_of_available_simple_commands;
	int						number_of_simple_commands;
	t_simple_command		**simple_commands;
	int						current_simple_command;
	int						original_fdin;
	int						original_fdout;
}				t_command;

//	simple_commands:

t_simple_command	*new_simple_command(void);
void				destroy_simple_command(t_simple_command *simple_command);
int					insert_argument(t_simple_command *simple_command,
						char *argument);
int					malloc_arguments(t_simple_command *simple_command);

//	commands:

t_command			*new_command(void);
void				destroy_command(t_command *command);
int					insert_simple_command(t_command *command,
						t_simple_command *simple_command);
int					malloc_simple_commands(t_command *command);
t_simple_command	*get_current_simple_command(t_command *command);

#endif
