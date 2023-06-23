/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:06:02 by josanton          #+#    #+#             */
/*   Updated: 2023/06/23 13:29:49 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_token(char *str, int i, int tk_len, int index)
{
	ft_strncpy(_input()->token_matrix[index], \
			str + i, tk_len);
	_input()->token_matrix[index][tk_len] = '\0';
}

void	tokenizer(char *str, int i)
{
	int	len;
	int	tk_len;

	len = matrix_len(str);
	_input()->token_matrix = malloc(sizeof(char *) * (len + 1));
	if (!_input()->token_matrix)
		return ;
	_input()->token_matrix[len] = NULL;
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
			if (!_input()->token_matrix[_input()->index])
				return ;
			copy_token(str, i, tk_len, _input()->index);
			_input()->index++;
			i = i + tk_len;
		}
	}
}

int	get_command_len(int i)
{
	int	len;

	len = 0;
	while (_input()->new_token_matrix[i]
		&& _input()->new_token_matrix[i][0] != '|')
	{
		len++;
		i++;
	}
	return (len);
}

void	get_token_list(t_token **token_lst, int i)
{
	int	cmd_len;

	info()->nr_pipe = 0;
	while (_input()->new_token_matrix[i])
	{
		cmd_len = 0;
		if (_input()->new_token_matrix[i]
			&& _input()->new_token_matrix[i][0] == '|')
		{
			add_back(token_lst, new_token("Operator", 1, i));
			info()->nr_pipe++;
			i++;
		}
		else
		{
			cmd_len = get_command_len(i);
			add_back(token_lst, new_token("Command", cmd_len, i));
			i = i + cmd_len;
		}
	}
}

void	analyze_and_parse(char *str)
{
	t_token	*token_lst;
	t_token	*temp;

	tokenizer(str, 0);
	_input()->new_token_matrix = handle_expansion(_input()->token_matrix);
	token_lst = NULL;
	temp = token_lst;
	get_token_list(&temp, 0);
	token_lst = temp;
	parse_commands(token_lst);
	free_list(&temp);
}
