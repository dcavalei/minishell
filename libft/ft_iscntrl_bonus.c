/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscntrl_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmartins <rmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:25:53 by rmartins          #+#    #+#             */
/*   Updated: 2021/02/12 10:49:22 by rmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iscntrl(int c)
{
	if ((c >= 0 && c < 32) || c == 127)
		return (1);
	else
		return (0);
}
