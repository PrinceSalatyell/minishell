/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:12:32 by josanton          #+#    #+#             */
/*   Updated: 2023/06/23 13:08:02 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_char_arg(char *str, int i)
{
	int		j;
	int		len;
	char	*exit_num_str;

	j = i;
	len = 0;
	while (str[i] && str[i++] != 32)
	{
		len++;
	}
	exit_num_str = malloc(sizeof(char) * (len + 1));
	if (!exit_num_str)
		return ;
	len = 0;
	while (str[j] && str[j] != 32)
	{
		exit_num_str[len] = str[j];
		j++;
		len++;
	}
	exit_num_str[len] = '\0';
	printf("exit: %s: numeric argument required\n", exit_num_str);
	free(exit_num_str);
	free(str);
	exit_minishell(2);
}

void	exit_char_arg2(char *str, int i, int j, int len)
{
	char	*exit_num_str;

	while (str[i] && str[i] != 32)
	{
		i++;
		len++;
	}
	exit_num_str = malloc(sizeof(char) * (len + 1));
	if (!exit_num_str)
		return ;
	len = 0;
	while (str[j] && str[j] != 32)
	{
		exit_num_str[len] = str[j];
		j++;
		len++;
	}
	exit_num_str[len] = '\0';
	printf("exit: %s: numeric argument required\n", exit_num_str);
	free(exit_num_str);
	free(str);
	exit_minishell(2);
}

void	exit_single_num_arg(char *str, int j, int len)
{
	int		exit_code_num;
	char	*exit_num_str;

	exit_num_str = malloc(sizeof(char) * (len + 1));
	if (!exit_num_str)
		return ;
	len = 0;
	while (str[j] && str[j] != 32)
	{
		exit_num_str[len] = str[j];
		j++;
		len++;
	}
	exit_num_str[len] = '\0';
	exit_code_num = ft_atoi(exit_num_str);
	free(exit_num_str);
	free(str);
	printf("Exit\n");
	exit_minishell(exit_code_num);
}

void	exit_num_arg(char *str, int i)
{
	int	j;
	int	len;

	j = i;
	len = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		i++;
		len++;
	}
	if (str[i] && str[i] != 32)
		exit_char_arg2(str, i, j, len);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '\0')
		exit_single_num_arg(str, j, len);
	else
	{
		printf("exit: too many arguments\n");
		info()->error_code = 1;
		info()->exit_flag = true;
		return ;
	}
}

void	check_if_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (ft_strncmp(str + i, "exit", 4))
		return ;
	i = i + 4;
	if (str[i] && str[i] != 32)
		return ;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '\0')
	{
		printf("Exit\n");
		free(str);
		exit_minishell(info()->error_code);
	}
	else if (str[i] >= 48 && str[i] <= 57)
		exit_num_arg(str, i);
	else
		exit_char_arg(str, i);
}
