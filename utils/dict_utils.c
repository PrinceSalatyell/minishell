/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:55:18 by josanton          #+#    #+#             */
/*   Updated: 2023/06/23 13:25:35 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_dict	*curr;
	t_dict	*next;

	if (!dict)
		return ;
	curr = *dict;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	*dict = NULL;
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

void	ft_dictdel(t_dict **dict, char *key)
{
	t_dict	*prev;
	t_dict	*curr;

	prev = NULL;
	curr = *dict;
	while (curr != NULL)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev == NULL)
				*dict = curr->next;
			else
				prev->next = curr->next;
			free(curr->key);
			if (curr->value && curr->value[0])
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
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
