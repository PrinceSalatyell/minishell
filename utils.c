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

void	free_list(t_token **token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->value);
		free((*token)->type);
		free(*token);
		*token = tmp;
	}
}

t_token	*lst_last(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	while (token_lst->next)
		token_lst = (token_lst)->next;
	return (token_lst);
}

void	add_back(t_token **token_lst, t_token *new)
{
	if (!new)
		return ;
	if (!*token_lst)
		*token_lst = new;
	else
		(lst_last(*token_lst))->next = new;
}

t_token	*new_token(char *value, char *type)
{
	t_token	*token_node;

	token_node = malloc(sizeof(t_token));
	if (!token_node)
		return (NULL);
	token_node->value = ft_strdup(value);
	token_node->type = ft_strdup(type);
	token_node->next = NULL;
	return (token_node);
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
