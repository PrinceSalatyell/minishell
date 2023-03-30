/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:55:18 by josanton          #+#    #+#             */
/*   Updated: 2023/03/30 12:50:40 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dictadd_back(t_dict **dict, t_dict *new)
{
	t_dict	*temp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = (*lst);
	while (temp->next)
		(temp) = temp->next;
	temp->next = new;
}

void	ft_dictclear(t_list **dict)
{
	t_dict	*temp;

	if (!dict)
		return ;
	if (!(*dict))
		return ;
	while (*dict)
		ft_dictdellast(*dict);
}

t_dict	*ft_dictnew(char *key, char *value)
{
	t_dict	*temp;

	temp = malloc(sizeof(t_dict));
	if (!temp)
		return (NULL);
	temp->key = key;
	temp->value = value;
	temp->next = NULL;
	return (temp);
}

void	ft_dictdellast(t_dict *dict)
{
	t_dict	*temp;

	temp = dict;
	if (!temp->next)
	{
		free(temp->key);
		free(temp->value);
		free(temp);
		return ;
	}
	while (temp->next->next)
		temp = temp->next;
	free(temp->next->key);
	free(temp->next->value);
	free(temp->next);
	temp->next = NULL;
}

int	ft_dictsize(t_dict *dict)
{
	int	num;

	num = 0;
	while (dict)
	{
		num++;
		dict = dict->next;
	}
	return (num);
}
