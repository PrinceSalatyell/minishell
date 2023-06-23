/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:07 by josanton          #+#    #+#             */
/*   Updated: 2023/06/23 13:38:12 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input	*_input(void)
{
	static t_input	input;

	return (&input);
}

t_info	*info(void)
{
	static t_info	info;

	if (!info.shlvl)
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
		info.home = getenv("HOME");
	}
	return (&info);
}
