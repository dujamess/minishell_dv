/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 02:36:14 by khmessah          #+#    #+#             */
/*   Updated: 2024/03/30 00:21:44 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct pipex
{
	char	**commande;
	int		i;
	int		j;
	int		h;
	char	*s;
	char	**stock;
	int		fd;
	int		fd1;
	char	*path_commande1;
	char	*path_commande2;
	int		tab[2];
	pid_t	e;
	pid_t	lastpid;
}	t_pipex;

void	free_d(char **str);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_sep_mot(char *str, char sep, int ptr);
char	*ft_locmot(char *str, int *ptr, char sep);
int		ft_countr_mot(char *s, char c);
char	**ft_split(char *s, char c);
char	**env_split(char **env, t_pipex *p);
char	*join_commande_path(char **stock, char *av, t_pipex *pipex);
void	child_process1(char **av, t_pipex *pipex, char **env);
void	child_process2(char **av, t_pipex *pipex, char **env, int ac);
void	wait_process(t_pipex *pipex);

#endif