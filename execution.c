#include "minishell.h"
void    split_path(t_variable  *env,t_path *path)
{
    int i;
    int h;
    char *v;
    h = 0;
    i = 0;
    while(env[i].nom)
    {
        if (ft_strcmp(env[i].nom,"PATH") == 0)
        {
            path->var_path = ft_split(env[i].valeur,':');
            while(path->var_path[h])
            {
                v = path->var_path[h];
                path->var_path[h] = ft_strjoin(path->var_path[h],"/");
                free(v);
                h++;
            }
            break;
        }
        i++;
    }
}

char	*join_commande_path(t_path *path, char *av)
{
	char	*path_commande;
	int		h;
	h = 0;

	path->option = ft_split(av, ' ');
	while (path->var_path[h])
	{
		path_commande = ft_strjoin(path->var_path[h], path->option[0]);
		if (access(path_commande, F_OK) == 0)
			return (path_commande);
		free(path_commande);
		h++;
	}
	return (NULL);
}

void    execution_cmd(int ac,char *av,t_variable *env,t_path *path)
{
    int nb_cmd;
    int i;
    int pid;
    i = 0;
    nb_cmd = ac;
    char **split = ft_split(av,' ');
    int pipes[nb_cmd][2];
    while (i < nb_cmd - 1)
    {
        if (pipe(pipes[i]) == -1) 
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    // int fd;
    while (i < nb_cmd)
    {
        pid = fork();
        if ( pid == 0)
        {
            if (i!= 0)
            {
                dup2(pipes[i - 1][0],STDIN_FILENO);
                close(pipes[i - 1][1]);
            }
            if (i != nb_cmd - 1)
            {
                dup2(pipes[i][1],STDOUT_FILENO);
                close(pipes[i][0]);
            }
            char *s = join_commande_path(path, split[i]);
            execve(s,path->option,(char **)env);
        }
        i++;
    }
     i = 0;
    while (i < nb_cmd - 1) 
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
    i = 0;
    while (i < nb_cmd) 
    {
        wait(NULL);
        i++;
    }
}