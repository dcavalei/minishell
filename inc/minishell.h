/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:24:57 by dcavalei          #+#    #+#             */
/*   Updated: 2021/12/21 14:31:40 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "ft_ansi.h"
# include "command_data.h"

# define PROMPT_MAX 4096
# define BUFFER_SIZE 32
# define DEFAULT_SIZE 32
# define ENV_REALLOC_SIZE 32
# define TMP_STDIN_PATH "/tmp/._tmp_stdin"

# ifndef PATH_MAX
#  define PATH_MAX 4096 // linux error i've no f clue but this fix
# endif

typedef struct s_error
{
	int		error;
	char	*command_name;
	char	*argument;
}				t_error;

typedef struct s_env
{
	char	**env;
	int		number_of_available_variables;
	int		number_of_variables;
}				t_env;

typedef struct s_data
{
	char				prompt[PROMPT_MAX];
	t_env				env;
	t_command			*cmd;
	char				**res;
	char				*input;
	char				*user;
	char				*home;
	int					exit;
	int					i;
}				t_data;

/*
**
*/

int		parse_str(t_data *data, char **str);
void	parse_simple_command_args(t_data *data);
int		print_error(char *shell_name, char *command_name,
			char *argument, char *error);
int		realloc_env(t_env *env);
int		set_up_env(t_data *data, char **env);
int		init_data(t_data *data, char **env);
void	free_env(t_env env);

/*
**	src/builtins/
*/

/*
**	src/builtins/cd/
*/

int		cmd_cd(t_data *data);
int		get_env_index(t_env env, char *str);
void	pwd_oldpwd_handler(t_data *data);

int		cmd_cd_tilde(t_data *data, t_simple_command *simple_command);
int		cmd_cd_home_relative_path(t_data *data,
			t_simple_command *simple_command);
int		cmd_cd_minus(t_data *data);
int		cmd_cd_default(t_data *data, t_simple_command *simple_command);

/*
**	src/builtins/export/
*/

int		cmd_export(t_data *data);

int		*get_valid_name_index_array(t_simple_command *simple_command);
int		check_name(char *str);

/*
**	src/builtins	files
*/

int		cmd_echo(t_data *data);
int		cmd_env(t_data *data);
char	*my_get_env(t_env env, char *name);
int		cmd_exit(t_data *data);
int		cmd_pwd(t_data *data);
int		cmd_unset(t_data *data);
int		substitute_env(t_env *env, char *str, int index);

/*
**
*/

int		is_special_input(char *string);

int		overwrite_handler(t_data *data,
			t_simple_command *simple_command, int *i);
int		append_handler(t_data *data,
			t_simple_command *simple_command, int *i);

int		redir_handler(t_data *data,
			t_simple_command *simple_command, int *i);

int		stdin_redir_handler(t_data *data,
			t_simple_command *simple_command, int *i);

int		build_command(t_data *data);

void	print_newline(int signal_num);
void	sigquit_handler(int signal_num);

int		ft_get_next_line(int fd, char **line);

int		init_env(t_data	*data, char **env);

void	build_prompt(t_data *data);

void	ft_print_split(char **str);
char	**ft_parser(char *str);
int		execute_command(t_simple_command *cmd, char **env);
void	run_commands(t_data *d, int number_cmds);

void	save_original_fd(t_data *d);
void	restore_and_close_file_descritors(t_data *d);
int		set_fdin(t_command *cmd, int current_cmd);
int		set_fdout(t_command *cmd, int current_cmd);

/*
**	debug
*/

void	show_simple_command(t_simple_command *simple_command,
			int show_null_arguments);
void	show_command(t_command *command, int show_null_arguments);

#endif
