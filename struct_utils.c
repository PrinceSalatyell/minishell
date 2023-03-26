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