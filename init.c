/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:07 by josanton          #+#    #+#             */
/*   Updated: 2023/05/12 17:34:18 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*_input(void)
{
	static t_input	input;

	return (&input);
}

t_info	*info(void)
{
	static t_info	info;

	if (!info.path)
	{
		if (getenv("SHLVL"))
		{
			if (ft_atoi(getenv("SHLVL")) >= 0)
				info.shlvl = ft_atoi(getenv("SHLVL")) + 1;
			else
				info.shlvl = 0;
		}
		else
			info.shlvl = 1;
		(info.path) = ft_split(getenv("PATH"), ':');
		info.home = getenv("HOME");
	}
	return (&info);
}
