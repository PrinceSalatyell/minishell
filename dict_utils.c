/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:55:18 by josanton          #+#    #+#             */
/*   Updated: 2023/04/01 15:41:31 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dictadd_back(t_dict **dict, t_dict *new)
{
	t_dict	*temp;

	if (!dict || !new)
		return ;
	if (!(*dict))
	{
		*dict = new;
		return ;
	}
	temp = (*dict);
	while (temp->next)
		(temp) = temp->next;
	temp->next = new;
}

void	ft_dictclear(t_dict **dict)
{
	if (!dict)
		return ;
	if (!(*dict))
		return ;
	while (*dict)
		ft_dictdellast(dict);
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

// ft_dictdel(t_dict *dict, char *key)
// {
// 	t_dict *temp;

// 	while(dict)
// 	{
// 		if (!ft_strcmp(dict->key, key))
// 		{

// 		}
// 	}
// }

void	ft_dictdellast(t_dict **dict)
{
	t_dict	*head;

	if (!dict || !(*dict))
		return ;
	head = *dict;
	if (!(*dict)->next)
	{
		free((*dict)->key);
		free((*dict)->value);
		free((*dict));
		(*dict) = NULL;
		return ;
	}
	while ((*dict)->next->next)
		(*dict) = (*dict)->next;
	free((*dict)->next->key);
	free((*dict)->next->value);
	free((*dict)->next);
	(*dict)->next = NULL;
	(*dict) = head;
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
