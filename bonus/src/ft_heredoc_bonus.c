/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:24:33 by jdasilva          #+#    #+#             */
/*   Updated: 2022/11/19 21:08:28 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

void	ft_write_pipe(int *fd, char *delimiter)
{
	char	*line;

	close(fd[READ_END]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) - 1) == 0)
		{
			free(line);
			close(fd[WRITE_END]);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	ft_heredoc(int argc, char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (argc < 6)
		ft_perror("Error Argument");
	if (pipe(fd) == -1)
		ft_perror("Error Pipe");
	pid = fork();
	if (pid == -1)
		ft_perror("Error Pid");
	if (pid == 0)
		ft_write_pipe(fd, argv[2]);
	else
	{
		close(fd[WRITE_END]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_perror("Error");
		close(fd[READ_END]);
	}
	waitpid(pid, NULL, 0);
}
