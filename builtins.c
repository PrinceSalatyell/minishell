/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:47:15 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/20 19:00:57 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	echo(char *str, bool nl)
{
	bool	success;

	success = false;
	if (str && *str)
	{
		printf("%s", str);
		success = true;
	}
	if (nl)
		printf("\n");
	return (success);
}
