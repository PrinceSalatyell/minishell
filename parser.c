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

int	copy_token(char *str, int i, int tk_len, int index)
{
	if (str[i] == '"' || str[i] == 39)
	{
		ft_strncpy(_input()->token_matrix[index], \
			str + i + 1, tk_len);
		_input()->token_matrix[index][tk_len] = '\0';
		return (tk_len + 2);
	}
	else
	{
		ft_strncpy(_input()->token_matrix[index], \
				str + i, tk_len);
		_input()->token_matrix[index][tk_len] = '\0';
		return (tk_len);
	}
}

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
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
		if (str[i] && (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32))
		{
			tk_len = token_len(str, i);
			_input()->token_matrix[_input()->index] = \
			malloc(sizeof(char *) * (tk_len + 1));
			tk_len = copy_token(str, i, tk_len, _input()->index);
			_input()->index++;
			i = i + tk_len;
		}
	}
}

void	get_token_list(t_token **token_lst, int i)
{
	int	flag;

	flag = 0;
	while (_input()->token_matrix[i])
	{
		if (flag == 0)
		{
			add_back(token_lst, new_token(_input()->token_matrix[i], "Command"));
			flag++;
		}
		else if (flag == 1)
		{
			if (_input()->token_matrix[i][0] == '|')
				flag++;
			if (flag == 2)
			{
				add_back(token_lst, new_token(_input()->token_matrix[i], "Operator"));
				flag = 0;
			}
			else
				add_back(token_lst, new_token(_input()->token_matrix[i], "Argument"));
		}
		i++;
	}
}

void	parse_commands(t_token *token_lst)
{
	int	nr_commands;

	nr_commands = 0;
	if (token_lst)
	{
		while (token_lst->next)
		{
			if (ft_strcmp(token_lst->type, "Operator") == 0)
				nr_commands++;
			token_lst = token_lst->next;
		}
	}
	printf("nr_commands - %d\n", nr_commands);
}

void	analyze_and_parse(char *str)
{
	//t_token	*token_lst;

	tokenizer(str, 0);
	// token_lst = NULL;
	// get_token_list(&token_lst, 0);
	// if (token_lst)
	// {
	// 	while (token_lst->next)
	// 	{
	// 		printf("value - %s\ntype - %s\n------------\n", token_lst->value, token_lst->type);
	// 		token_lst = token_lst->next;
	// 	}
	// 	printf("value - %s\ntype - %s\n", token_lst->value, token_lst->type);
	// }
	// parse_commands(token_lst);
	// free_list(&token_lst);
}
