/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:24:19 by timartin          #+#    #+#             */
/*   Updated: 2023/06/23 13:25:55 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_token **token)
{
	t_token	*tmp;
	int		i;

	if (!token)
		return ;
	while (*token)
	{
		i = 0;
		tmp = (*token)->next;
		while ((*token)->value[i])
		{
			free((*token)->value[i]);
			i++;
		}
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

t_token	*new_token(char *type, int len, int i)
{
	t_token	*token_node;

	token_node = malloc(sizeof(t_token));
	if (!token_node)
		return (NULL);
	token_node->value = malloc(sizeof(token_node->value) * (len + 1));
	if (!token_node->value)
		return (NULL);
	if (ft_strcmp(type, "Operator") != 0)
		cpy_command(&token_node, i, 0);
	else
		token_node->value[0] = ft_strdup(_input()->new_token_matrix[i]);
	token_node->value[len] = NULL;
	token_node->type = ft_strdup(type);
	token_node->next = NULL;
	return (token_node);
}
