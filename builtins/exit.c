#include "../minishell.h"

void    exit_char_arg(char *str, int i)
{
    int j;
    int len;
    char    *exit_num_str;

    j = i;
    len = 0;
    while (str[i] && str[i] != 32)
    {
        i++;
        len++;
    }
    exit_num_str = malloc(sizeof(char) * (len + 1));
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
    exit(2);
}

void    exit_char_arg2(char *str, int i, int j, int len)
{
    char    *exit_num_str;

    while (str[i] && str[i] != 32)
    {
        i++;
        len++;
    }
    exit_num_str = malloc(sizeof(char) * (len + 1));
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
    exit(2);
}

void    exit_single_num_arg(char *str, int j, int len)
{
    int exit_code_num;
    char    *exit_num_str;

    exit_num_str = malloc(sizeof(char) * (len + 1));
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
    exit(exit_code_num);
}

void    exit_num_arg(char *str, int i)
{
    int j;
    int len;

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
	if(str[i] == '\0')
	{
		printf("Exit\n");
		free(str);
		exit(0);
	}
	else if (str[i] >= 48 && str[i] <= 57)
        exit_num_arg(str, i);
	else
        exit_char_arg(str, i);
}
