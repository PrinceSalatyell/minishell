/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:04:07 by josanton          #+#    #+#             */
/*   Updated: 2023/03/22 21:29:01 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*_input(void)
{
	static t_input	input;

	return (&input);
}

t_token	*token_node(void)
{
	static t_token	token;

	return (&token);
}