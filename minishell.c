#include "minishell.h"

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}
void    print_env(t_variable *my_env)
{
    int i;

    i = 0;
    while (my_env && my_env[i].nom != NULL && my_env[i].valeur != NULL) 
    {
        printf("%s=%s\n", my_env[i].nom, my_env[i].valeur);
        i++;
    }
}

int main(int ac,char **av,char **env)
{
    (void)ac;
    (void)av;
    int s = 0;
    t_variable *my_env = builtin_env(env);
    augment_level_shlvl(my_env);
    t_path *path =  malloc(sizeof(t_path));
    while(1)
    {
        char *line = readline("mini_minishell$ ");
        if (line)
			add_history(line);
        char **split = ft_split(line,' ');
        s = 0;
        while(split[s])
            s++;
        split_path(my_env,path);
        if (split[1]&&ft_strcmp(split[1],"<<") == 0)
               heredoc(split[2]);
        else if (split[0]&& ft_strcmp(split[0], "pwd") == 0)
           builtin_pwd();
        else if (split[0] && ft_strcmp(split[0], "env") == 0)
            print_env(my_env);
        else if (split[0]&& ft_strcmp(split[0], "echo") == 0)
            builtin_echo(s,split);
        else if (split[0] && ft_strcmp(split[0], "cd") == 0)
            builtin_cd(s,split,my_env);
        else if (split[0] && ft_strcmp(split[0], "exit") == 0)
            builtin_exit(s,split);
        else if(split[0] && ft_strcmp(split[0],"unset") == 0)
            my_env = builtin_unset(split,my_env);
        else if(split[0] && ft_strcmp(split[0],"export") == 0)
            my_env = builtin_export(split,my_env);
        else
             execution_cmd(s,line,my_env,path);
    }
}