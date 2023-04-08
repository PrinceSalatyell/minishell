/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:07 by josanton          #+#    #+#             */
/*   Updated: 2023/03/24 20:23:07 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(void)
{
	info()->nr_op = 0;
	info()->nr_pipe = 0;
}

t_input	*_input(void)
{
	static t_input	input;

	return (&input);
}

t_info	*info(void)
{
	static t_info	info;

	if (!info.path)
		(info.path) = ft_split(getenv("PATH"), ':');
	return (&info);
}
