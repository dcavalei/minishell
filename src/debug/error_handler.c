/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:30:34 by dcavalei          #+#    #+#             */
/*   Updated: 2021/10/14 12:30:34 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *shell_name, char *command_name,
	char *argument, char *error)
{
	if (shell_name)
		printf("%s: ", shell_name);
	if (command_name)
		printf("%s: ", command_name);
	if (argument)
		printf("%s: ", argument);
	if (error)
	{
		if (!ft_strcmp(error, "errno"))
			printf("%s", strerror(errno));
		else
			printf("%s", error);
	}
	printf("\n");
	return (1);
}
