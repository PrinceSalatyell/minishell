/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/03/26 19:07:22 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_commands(t_token *token_lst)
{
	// if (!is_builtin(_input()->command))
	// if (token_lst->value[0][0] == '"')
	// 	token_lst = rm_quotes(token_lst, token_lst->value[0]);
	// printf("heyy\n");
	// printf("value -> %s\n", token_lst->value[0]);
	//token_lst = temp;
	execute(token_lst);
}