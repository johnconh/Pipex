/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:55:58 by jdasilva          #+#    #+#             */
/*   Updated: 2022/11/21 17:39:47 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	ft_execve(char *argv, char **envp)
{
	char	**rutas;
	char	**cmd;
	int		i;

	cmd = ft_split(argv, ' ');
	rutas = get_rutas(envp);
	if (rutas == NULL)
		ft_perror("Error PATH");
	i = 0;
	while (rutas[i])
	{
		rutas[i] = ft_strjoin(rutas[i], "/");
		rutas[i] = ft_strjoin(rutas[i], cmd[0]);
		if (access(rutas[i], F_OK) == 0)
			execve(rutas[i], cmd, envp);
		i++;
	}
	ft_free_split(rutas);
	ft_free_split(cmd);
	ft_perror("Error");
}

void	ft_cmd_1(int *fd, char **argv, char **envp)
{
	int		infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		ft_perror("Error infile:");
	if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		ft_perror("ERROR");
	if (dup2(infile, STDIN_FILENO) == -1)
		ft_perror("ERROR");
	close(fd[READ_END]);
	close(infile);
	close(fd[WRITE_END]);
	ft_execve(argv[2], envp);
}

void	ft_cmd_2(int *fd, char **argv, char **envp)
{
	int		outfile;

	outfile = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (outfile < 0)
		ft_perror("Error infile:");
	if (dup2(fd[READ_END], STDIN_FILENO) == -1)
		ft_perror("ERROR");
	if (dup2 (outfile, STDOUT_FILENO) == -1)
		ft_perror("ERROR");
	close(fd[WRITE_END]);
	close(outfile);
	close(fd[READ_END]);
	ft_execve(argv[3], envp);
}

void	pipex_main(char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		ft_perror("Pipe Error");
	pid1 = fork();
	if (pid1 == -1)
		ft_perror("Pid1 Error");
	if (pid1 == 0)
		ft_cmd_1(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_perror("Pid2 Error");
	if (pid2 == 0)
		ft_cmd_2(fd, argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(2, "Argumentos invalidos\n", 21);
		exit (-1);
	}
	pipex_main(argv, envp);
	return (0);
}
