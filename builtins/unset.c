/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:12:39 by salatiel          #+#    #+#             */
/*   Updated: 2023/04/05 18:16:17 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **command)
{
	int		i;
	char	*key;

	i = -0;
	while (command[++i])
	{
		key = get_key(command[i]);
		ft_dictdel(&(info()->env), key);
	}
}