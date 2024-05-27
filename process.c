/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:19:59 by khmessah          #+#    #+#             */
/*   Updated: 2024/03/30 03:56:49 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**env_split(char **env, t_pipex *p)
{
	p->i = 0;
	p->j = 0;
	p->h = 0;
	while (env[p->i])
	{
		p->j = 0;
		while (env[p->i][p->j])
		{
			if (p->j == 0 && env[p->i][p->j] == 'P'
				&& env[p->i][p->j + 4] == '=')
			{
				p->stock = ft_split(env[p->i] + 5, ':');
				while (p->stock[p->h])
				{
					p->s = p->stock[p->h];
					p->stock[p->h] = ft_strjoin(p->stock[p->h], "/");
					free(p->s);
					p->h++;
				}
			}
			p->j++;
		}
		p->i++;
	}
	return (p->stock);
}

char	*join_commande_path(char **stock, char *av, t_pipex *pipex)
{
	char	*path_commande;
	int		h;

	h = 0;
	pipex->commande = ft_split(av, ' ');
	while (stock[h])
	{
		path_commande = ft_strjoin(stock[h], pipex->commande[0]);
		if (access(path_commande, F_OK) == 0)
			return (path_commande);
		free(path_commande);
		h++;
	}
	return (NULL);
}

void	child_process1(char **av, t_pipex *pipex, char **env)
{
	pipex->path_commande1 = join_commande_path(pipex->stock, av[2], pipex);
	if (pipex->path_commande1 == NULL)
	{
		write(2, av[2], ft_strlen(av[2]));
		write(2, ":", 1);
		write(2, "command not found\n", 19);
		exit(127);
	}
	pipex->fd = open(av[1], O_RDONLY);
	if (pipex->fd < 0)
	{
		write(1, "no such file or directory: ", 28);
		write(1, av[1], ft_strlen(av[1]));
		exit(1);
	}
	dup2(pipex->fd, STDIN_FILENO);
	dup2(pipex->tab[1], STDOUT_FILENO);
	close(pipex->tab[0]);
	if (execve(pipex->path_commande1, pipex->commande, env) == -1)
	{
		perror(av[3]);
		exit(126);
	}
	free(pipex->path_commande1);
	free_d(pipex->commande);
}

void	child_process2(char **av, t_pipex *pipex, char **env, int ac)
{
	pipex->path_commande2 = join_commande_path(pipex->stock, av[3], pipex);
	if (pipex->path_commande2 == NULL)
	{
		write(2, av[3], ft_strlen(av[3]));
		write(2, ":", 1);
		write(2, "command not found\n", 19);
		exit(127);
	}
	pipex->fd1 = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (pipex->fd1 < 0)
		exit(1);
	dup2(pipex->tab[0], STDIN_FILENO);
	dup2(pipex->fd1, STDOUT_FILENO);
	close(pipex->tab[1]);
	if (execve(pipex->path_commande2, pipex->commande, env) == -1)
	{
		perror(av[3]);
		exit(126);
	}
	free(pipex->path_commande2);
	free_d(pipex->commande);
}

void	wait_process(t_pipex *pipex)
{
	int		s;

	pipex->e = wait(&s);
	while (pipex->e != -1)
	{
		if (pipex->e == pipex->lastpid)
			exit(WEXITSTATUS(s));
		pipex->e = wait(&s);
	}
	free_d(pipex->stock);
}
