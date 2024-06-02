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
# include <string.h>
# include <limits.h>
#include <readline/readline.h>
#include <readline/history.h> 

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

typedef struct variable_glob
{
	char	*OLDPWD;
	char	*PWD;
	char	*HOME;
	char	*SHLVL;
}	t_variable_glob;

typedef struct variable
{
    char *nom;
    char *valeur;
}t_variable;



char   *builtin_pwd();
t_variable *builtin_unset(int ac,char **av,t_variable *env);
void    builtin_exit(int ac,char **av);
void    builtin_echo(int ac,char **av,int t);
int    builtin_cd(int ac,char **av,t_variable *my_env);
t_variable *builtin_env(char **env);
t_variable split_env(char *env_line);
void	free_d(char **str);
char	*ft_strdup(const char *s);
int	ft_atoi(const char *str);
int ft_strcmp(char *s1, char *s2);
int count_env(char **env);
char	*ft_strchr(const char *s, int c);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
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