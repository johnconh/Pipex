/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:03:15 by jdasilva          #+#    #+#             */
/*   Updated: 2022/11/19 21:19:29 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

char	**get_rutas(char **envp)
{
	int		i;
	char	**rutas;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			rutas = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (rutas);
}

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	ft_open(char *path, char flags)
{
	int	fd;

	fd = -1;
	if (flags == 'r')
		fd = open(path, O_RDONLY);
	else if (flags == 'w')
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (flags == 'a')
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		ft_perror("Error file");
	return (fd);
}
