/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:55:58 by jdasilva          #+#    #+#             */
/*   Updated: 2022/11/21 20:41:47 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

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
		rutas[i] = ft_strjoin(rutas[i], "/", 1);
		rutas[i] = ft_strjoin(rutas[i], cmd[0], 1);
		if (access(rutas[i], F_OK) == 0)
			execve(rutas[i], cmd, envp);
		i++;
	}
	ft_free_split(rutas);
	ft_free_split(cmd);
	ft_perror("Error");
}

void	ft_pipex(char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		ft_perror("Error Pipe");
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ_END]);
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
			ft_perror("Error");
		close(fd[WRITE_END]);
		ft_execve(*argv, envp);
	}
	else
	{
		close(fd[WRITE_END]);
		if (dup2(fd[READ_END], STDIN_FILENO) == -1)
			ft_perror("ERROR");
		close(fd[READ_END]);
		waitpid(pid, NULL, 0);
	}
}

void	pipex_main(int argc, char **argv, char **envp)
{
	int	num;
	int	infile;
	int	outfile;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		num = 3;
		ft_heredoc(argc, argv);
		outfile = ft_open(argv[argc -1], 'a');
	}
	else
	{
		num = 2;
		infile = ft_open(argv[1], 'r');
		outfile = ft_open(argv[argc -1], 'w');
		if (dup2(infile, STDIN_FILENO) == -1)
			ft_perror("Error");
	}
	while (num < argc - 2)
		ft_pipex(&argv[num++], envp);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_perror("ERROR");
	ft_execve(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		write(2, "Argumentos insuficientes\n", 25);
		exit (-1);
	}	
	pipex_main(argc, argv, envp);
	return (0);
}
