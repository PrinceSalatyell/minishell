/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:08:05 by josanton          #+#    #+#             */
/*   Updated: 2023/03/22 21:38:59 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd(int	**fd)
{
	int	i;

	if (!fd)
		return ;
	i = 0;
	while (i < info()->nr_pipe)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

// t_token	*rm_quotes(t_token *token_lst, char *str)
// {
// 	t_token	*new_lst;
// 	int	i;
// 	int	len;

// 	len = ft_strlen(str);
// 	while (token_lst)
// 	{
// 		i = -1;
// 		while (token_lst->value[++i] && ft_strcmp(token_lst->type, "Command") == 0)
// 		{
// 			printf("i - %d | value -> %s\n", i, token_lst->value[i]);
// 			if (ft_strcmp(token_lst->value[i], str) == 0)
// 			{
// 				//token_lst->value[i] = malloc(sizeof(char) * (len - 1));
// 				token_lst->value[i] = realloc(token_lst->value[i], len + 1);
// 				token_lst->value[i] = ft_strdup(str);
// 				//token_lst->value[i][len - 2] = '\0';
// 				printf("i - %d | value -> %s\n", i, token_lst->value[i]);
// 				return (*token_lst);
// 			}
// 		}
// 		token_lst = token_lst->next;
// 	}
// 	return (*token_lst);
// }

// void	cpy_operator(t_token **token_lst, int i)
// {
// 	if (_input()->token_matrix[i] == '|')
// 		(*token_lst)->value[0] = ft_strdup(_input()->token_matrix[i]);
// 	else if (_input()->token_matrix[i] == '>' || _input()->token_matrix[i] == '<')
// 	{

// 	}
// }

void	cpy_command(t_token **token_lst, int i)
{
	int	j;
	int	len;

	j = 0;
	while (_input()->token_matrix[i] && _input()->token_matrix[i][0] != '|' &&
			_input()->token_matrix[i][0] != '>' && _input()->token_matrix[i][0] != '<')
	{
		if (_input()->token_matrix[i][0] == '"' || _input()->token_matrix[i][0] == 39)
		{
			len = ft_strlen(_input()->token_matrix[i]);
			(*token_lst)->value[j] = malloc(sizeof(char) * (len - 1));
			(*token_lst)->value[j] = ft_strncpy((*token_lst)->value[j], _input()->token_matrix[i] + 1, len - 2);
			(*token_lst)->value[j][len - 2] = '\0';
			i = i + 1;
			j++;
		}
		else
		{
			(*token_lst)->value[j] = ft_strdup(_input()->token_matrix[i]);
			i = i + 1;
			j++;
		}
	}
}

int	quotes_end(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
	}
	else if (str[i] == 39)
	{
		i++;
		while (str[i] && str[i] != 39)
			i++;
	}
	return (i);
}

char	*ft_strjoin_nl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
	}
	j = 0;
	str[i] = '\n';
	i++;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
