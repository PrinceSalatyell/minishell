/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:02:50 by josanton          #+#    #+#             */
/*   Updated: 2023/06/23 13:29:44 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (matrix)
	{
		i = 0;
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

int	qt_len(char *str, int i)
{
	int	len;
	int	qt;

	len = 0;
	qt = 0;
	while (str[i] && (str[i] == '"' || str[i] == 39))
	{
		qt++;
		len++;
		i++;
	}
	while (str[i] && qt != 0)
	{
		len++;
		if (str[i] == '"' || str[i] == 39)
		{
			qt--;
			if (qt == 0 && str[i + 1] != 32 && str[i + 1] != '\0')
				qt++;
		}
		i++;
	}
	return (len);
}

int	token_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (str[i + 1] == '>' || str[i + 1] == '<')
			len++;
		return (len + 1);
	}
	while (str[i] && !(str[i] >= 9 && str[i] <= 13) && str[i] != 32)
	{
		if (str[i] == '"' || str[i] == 39)
			return (qt_len(str, i));
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (len);
		len++;
		i++;
	}
	return (len);
}

int	separate_pipe(char *str, int *i, int len)
{
	if (str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
	{
		if (str[*i + 1] == '>' || str[*i + 1] == '<')
			*i = *i + 1;
		return (len + 1);
	}
	while (str[*i] && !(str[*i] >= 9 && str[*i] <= 13) && str[*i] != 32
		&& str[*i] != '|' && str[*i] != '>' && str[*i] != '<')
		*i = *i + 1;
	if (!str[*i] || ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32))
	{
		*i = *i - 1;
		return (len + 1);
	}
	else if (str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
	{
		if (str[*i + 1] == '>' || str[*i + 1] == '<')
			*i = *i + 1;
		return (len + 2);
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
