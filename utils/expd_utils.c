/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:29:14 by timartin          #+#    #+#             */
/*   Updated: 2023/06/23 13:53:50 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_expanded_len(char *old_str, int i, int len)
{
	char	*var_key;
	char	*var_value;

	while (old_str[i])
	{
		if (old_str[i] == '$')
		{
			var_key = get_var_key(old_str, i);
			var_value = get_var_value(var_key);
			len = len + ft_strlen(var_value);
			free(var_key);
			free(var_value);
			i++;
			while (old_str[i] && !(old_str[i] >= 9 && old_str[i] <= 13)
				&& old_str[i] != 32 && old_str[i] != 39 && old_str[i] != '"'
				&& old_str[i] != '$')
				i++;
			i--;
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*get_var_value(char *var_key)
{
	t_dict	*temp;
	char	*value;

	value = NULL;
	temp = info()->env;
	while (temp)
	{
		if (ft_strcmp (temp->key, var_key) == 0)
		{
			value = ft_strdup(temp->value);
			break ;
		}
		else if (!ft_strcmp(var_key, "?"))
		{
			value = ft_itoa(info()->error_code);
			break ;
		}
		temp = temp->next;
	}
	if (!value)
	{
		value = malloc(sizeof(char) * 1);
		value[0] = '\0';
	}
	return (value);
}

// recieves a str where str[i] is '$'
// returns the var name attached to it
// when str is "ola $a ola $b"
// if i = 5 -> returns 'a' | if i = 12 ->returns 'b'
// the var name can then be used as a key to search for the value in env list
char	*get_var_key(char *str, int i)
{
	char	*var_key;
	int		start;
	int		j;

	start = i;
	i++;
	while (str[i] && !(str[i] >= 9 && str[i] <= 13) && str[i] != 32
		&& str[i] != 39 && str[i] != '"' && str[i] != '$')
		i++;
	var_key = malloc(sizeof(char) * (i - start));
	j = 0;
	start++;
	while (start < i)
	{
		var_key[j] = str[start];
		start++;
		j++;
	}
	var_key[j] = '\0';
	return (var_key);
}

bool	is_expansion(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
