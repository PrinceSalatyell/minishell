#include "minishell.h"

char	*get_dir_path(char *cmd)
{
	char	*path;
	char	*file;

	path = NULL;
	path = getcwd(path, 100);
	if (!path)
		return (NULL);
	file = ft_strjoin_sep(path, cmd, '/');
	free(path);
	return (file);
}

// flag -> 0 - WR_TRUNC | 1 - WR_APPEND | 2 - RDONLY 
int	open_file(char *file, int flag)
{
	char	*full_path;
	int	fd;

	fd = 0;
	full_path = get_dir_path(file);
	if (flag == 0)
		fd = open(full_path, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (flag == 1)
		fd = open(full_path, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (flag == 2)
		fd = open(full_path, O_RDONLY | O_CLOEXEC);
	free(full_path);
	return (fd);
}

int	check_invalid_red(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' && cmd[i][1] == '<')
		{
			printf("Unexpected token '><'\n");
			return (1);
		}
		if (cmd[i][0] == '<' && cmd[i][1] == '>')
		{
			printf("Unexpected token '<>'\n");
			return (1);
		}
		i++;
	}
	return (0);
}
