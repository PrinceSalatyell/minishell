/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:02:50 by josanton          #+#    #+#             */
/*   Updated: 2023/03/22 21:29:00 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void)
{
	int	i;

	if (_input()->token_matrix)
	{
		i = 0;
		while (_input()->token_matrix[i])
		{
			free(_input()->token_matrix[i]);
			i++;
		}
		free(_input()->token_matrix);
	}
}

int	qt_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '"')
	{
		while (str[++i] != '"')
			len++;
	}
	else if (str[i] == 39)
	{
		while (str[++i] != 39)
			len++;
	}
	return (len);
}

int	token_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '|')
		len++;
	while (str[i] && !(str[i] >= 9 && str[i] <= 13) && str[i] != 32)
	{
		if (str[i] == '"')
			return (qt_len(str, i));
		else if (str[i] == 39)
			return (qt_len(str, i));
		if (str[i] == '|')
			return (len);
		len++;
		i++;
	}
	return (len);
}

int	matrix_len(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
		if (!str[i])
			return (len);
		if (str[i] == '"' || str[i] == 39)
		{
			i = quotes_end(str, i);
			len++;
		}
		else
			len = separate_pipe(str, &i, len);
	}
	return (len);
}
