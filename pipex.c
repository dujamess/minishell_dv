/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:46:50 by khmessah          #+#    #+#             */
/*   Updated: 2024/03/30 03:41:00 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}
void	execute1(char *argv, char **envp,t_pipex *pipex)
{
	pipex->stock = env_split(envp, pipex);
	char *path_commande1 = join_commande_path(pipex->stock, argv, pipex);
	execve(path_commande1, pipex->commande, envp);
}
void	child_process(char *argv, char **envp,t_pipex *pipex)
{
	pid_t	pid;
	int		fd[2];
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute1(argv, envp,pipex);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		i;
	int		t;

	if (ac == 5)
	{
		i = 0;
		pipe(pipex.tab);
		env_split(env, &pipex);
		while (i < 2)
		{
			t = fork();
			if (t != 0 && i == 1)
				pipex.lastpid = t;
			if (t == 0 && i == 0)
				child_process1(av, &pipex, env);
			else if (t == 0 && i == 1)
				child_process2(av, &pipex, env, ac);
			i++;
		}
		close(pipex.tab[0]);
		close(pipex.tab[1]);
		wait_process(&pipex);
	}
	else if (ac > 5)
	{
		i = 2;
			error();
		int infile = open(av[1], O_RDONLY);
		int outfile = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
		if (infile == -1|| outfile == -1)
		dup2(infile, STDIN_FILENO);
		if (ac == 2)
			execute1(av[1], env,&pipex);
		else
		{
			while (i < ac - 2)
				child_process(av[i++], env,&pipex);
			execute1(av[ac - 2], env,&pipex);
		}
	}
}
