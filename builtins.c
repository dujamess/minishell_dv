#include "pipex.h"

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

int main(int ac,char **av,char **env)
{
    int i = 1;
    int t = 0;
    int s = 0;
    t_variable *my_env = builtin_env(env);
    while(1)
    {
    char *line = readline("mini_minishell$ ");
    if (line)
			add_history(line);
    char **split = ft_split(line,' ');
     s = 0;
     while(split[s])
        s++;
        if (ft_strcmp(split[0], "pwd") == 0)
           builtin_pwd();
        else if (ft_strcmp(split[0], "env") == 0)
        {
            i = 0;
            while (my_env && my_env[i].nom != NULL && my_env[i].valeur != NULL) 
            {
                printf("%s=%s\n", my_env[i].nom, my_env[i].valeur);
                i++;
            }
        }
        else if ((s >= 1 && ft_strcmp(split[0], "echo") == 0) && (ft_strcmp(split[1], "-n") != 0))
        {
            t = 0;
             builtin_echo(s,split,t);
        }
        else if (( s >= 1 && ft_strcmp(split[0], "echo") == 0) && (ft_strcmp(split[1], "-n") == 0) && split[2]!= NULL)
        {
            t = 1;
            builtin_echo(s,split,t);
        }
        else if (ft_strcmp(split[0], "cd") == 0)
            builtin_cd(s,split,my_env);
        else if (ft_strcmp(split[0], "exit") == 0)
            builtin_exit(s,split);
        else if(ft_strcmp(split[0],"unset") == 0)
            my_env = builtin_unset(split,my_env);
        else if(ft_strcmp(split[0],"export") == 0)
            my_env = builtin_export(split,my_env);
    }
}