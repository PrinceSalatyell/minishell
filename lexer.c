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
			tk_len = copy_token(str, i, tk_len, _input()->index);
			_input()->index++;
			i = i + tk_len;
		}
	}
}

int	get_command_len(int i)
{
	int	len;

	len = 0;
	//printf("i - %d | len - %d\n", i, len);
	while (_input()->token_matrix[i] &&_input()->token_matrix[i][0] != '|')
	{
		len++;
		i++;
	}
	//printf("len - %d\n", len);
	return (len);
}

void	cpy_command(t_token **token_lst, int *i, int cmd_len)
{
	int	j;

	(void)cmd_len;
	j = 0;
	while (_input()->token_matrix[*i] &&_input()->token_matrix[*i][0] != '|')
	{
		(*token_lst)->value[j] = ft_strdup(_input()->token_matrix[*i]);
		*i = *i + 1;
		j++;
	}
	//printf("i - %d | j - %d | tk_value - %s\n", *i, j, (*token_lst)->value[j]);
}

void	get_token_list(t_token **token_lst, int i)
{
	//int	len;
	int	cmd_len;

	while (_input()->token_matrix[i])
	{
		if (_input()->token_matrix &&_input()->token_matrix[i][0] == '|')
		{
			add_back(token_lst, new_token("Operator", 1));
			(*token_lst)->value[0][0] = '|';
			(*token_lst)->value[0][1] = '\0';
			i++;
		}
		else
		{
			cmd_len = get_command_len(i);
			add_back(token_lst, new_token("Command", cmd_len));
			cpy_command(token_lst, &i, cmd_len);
			//printf("i - %d | cmd_len - %d\ntk_type - %s\n", i, cmd_len, (*token_lst)->type);
		}
	}
}

// void	get_token_list(t_token **token_lst, int i)
// {
// 	int	flag;

// 	flag = 0;
// 	while (_input()->token_matrix[i])
// 	{
// 		if (flag == 0)
// 		{
// 			add_back(token_lst, new_token(_input()->token_matrix[i], "Command"));
// 			flag++;
// 		}
// 		else if (flag == 1)
// 		{
// 			if (_input()->token_matrix[i][0] == '|')
// 				flag++;
// 			if (flag == 2)
// 			{
// 				add_back(token_lst, new_token(_input()->token_matrix[i], "Operator"));
// 				flag = 0;
// 			}
// 			else
// 				add_back(token_lst, new_token(_input()->token_matrix[i], "Argument"));
// 		}
// 		i++;
// 	}
// }

void	analyze_and_parse(char *str)
{
	t_token	*token_lst;
	t_token *temp;
	int	i;

	tokenizer(str, 0);
	token_lst = NULL;
	temp = token_lst;
	get_token_list(&temp, 0);
	token_lst = temp;
	if (token_lst)
	{
		while (token_lst)
		{
			i = 0;
			printf("value -> ");
			while (token_lst->value[i])
			{
				printf("%s ", token_lst->value[i]);
				i++;
			}
			printf(" --- type - %s\n------------\n", token_lst->type);
			token_lst = token_lst->next;
		}

	}
	//parse_commands(token_lst);
	free_list(&token_lst);
}
