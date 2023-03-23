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
