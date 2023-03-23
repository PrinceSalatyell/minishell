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

void	free_token(char **token_matrix)
{
	int	i;

	if (token_matrix)
	{
		i = 0;
		while (token_matrix[i])
		{
			free(token_matrix[i]);
			i++;
		}
		free(token_matrix);
	}
}

int	qt_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '"')
	{
		while (str[i] != '"')
		{
			i++;
			len++;
		}
	}
	else if (str[i] == 39)
	{
		while (str[i] != 39)
		{
			i++;
			len++;
		}
	}
	return (len + 1);
}

int	token_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && !(str[i] >= 9 && str[i] <= 13) && str[i] != 32)
	{
		if (str[i] == '"')
			return (qt_len(str, i));
		else if (str[i] == 39)
			return (qt_len(str, i));
		i++;
		len++;
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
		{
			while (str[i] && !(str[i] >= 9 && str[i] <= 13) && str[i] != 32)
				i++;
			if (!str[i])
				return (len + 1);
			len++;
		}
	}
	return (len);
}
