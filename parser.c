/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/03/22 21:47:02 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char *str, int i)
{
	int	len;
	int	tk_len;

	len = matrix_len(str);
	_input()->token_matrix = malloc(sizeof(char *) * (len + 1));
	if (!_input()->token_matrix)
		return ;
	_input()->token_matrix[len] = '\0';
	_input()->index = 0;
	while (str[i])
	{
		while (token_lst->next)
		{
			tk_len = token_len(str, i);
			_input()->token_matrix[_input()->index] = \
			malloc(sizeof(char *) * (tk_len + 1));
			ft_strncpy(_input()->token_matrix[_input()->index], \
			str + i, tk_len);
			_input()->token_matrix[_input()->index][tk_len] = '\0';
			_input()->index++;
			i = i + tk_len;
		}
	}
	printf("nr_commands - %d\n", nr_commands);
}
