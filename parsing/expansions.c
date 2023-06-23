/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:21:36 by timartin          #+#    #+#             */
/*   Updated: 2023/06/23 13:53:54 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cpy_var_value(char *new_str, char *old_str, int *i, int *k)
{
	char	*var_key;
	char	*var_value;
	int		j;

	var_key = get_var_key(old_str, *i);
	var_value = get_var_value(var_key);
	j = 0;
	while (var_value[j])
	{
		new_str[*k] = var_value[j];
		*k = *k + 1;
		j++;
	}
	*i = *i + 1;
	while (old_str[*i] && !(old_str[*i] >= 9 && old_str[*i] <= 13)
		&& old_str[*i] != 32 && old_str[*i] != 39
		&& old_str[*i] != '"' && old_str[*i] != '$')
		*i = *i + 1;
	free(var_value);
	free(var_key);
}

char	*replace_var(char *old_str, int len, int i, int k)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (len + 1));
	while (old_str[i])
	{
		if (old_str[i] == '$')
		{
			if (!old_str[i + 1] || (old_str[i + 1] >= 9 && old_str[i + 1] <= 13)
				|| old_str[i + 1] == 32 || old_str[i + 1] == '"'
				|| old_str[i + 1] == 39)
			{
				new_str[k++] = '$';
				i++;
			}
			else
				cpy_var_value(new_str, old_str, &i, &k);
		}
		else
			new_str[k++] = old_str[i++];
	}
	new_str[k] = '\0';
	return (new_str);
}

char	*expand_var(char *old_str)
{
	char	*new_str;
	int		len;

	if (old_str[0] == 39)
	{
		new_str = ft_strdup(old_str);
		return (new_str);
	}
	len = get_expanded_len(old_str, 0, 0);
	new_str = replace_var(old_str, len, 0, 0);
	return (new_str);
}

char	**handle_expansion(char **token_matrix)
{
	char	**new_token_matrix;
	int		i;

	i = 0;
	while (token_matrix[i])
		i++;
	new_token_matrix = malloc(sizeof(char *) * (i + 1));
	if (!new_token_matrix)
		return (NULL);
	i = 0;
	while (token_matrix[i])
	{
		if (is_expansion(token_matrix[i]) == true)
			new_token_matrix[i] = expand_var(token_matrix[i]);
		else
			new_token_matrix[i] = ft_strdup(token_matrix[i]);
		i++;
	}
	new_token_matrix[i] = NULL;
	return (new_token_matrix);
}
