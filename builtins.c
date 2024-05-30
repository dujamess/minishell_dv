#include "pipex.h"

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}
t_variable split_env(char *env_line) 
{
    t_variable var;
    char *delimiter_pos = ft_strchr(env_line, '=');
    if (delimiter_pos != NULL) 
    {
        int nom_length = delimiter_pos - env_line;
        var.nom = (char *)malloc(nom_length + 1);
        ft_strncpy(var.nom, env_line, nom_length);
        var.nom[nom_length] = '\0';
        var.valeur = strdup(delimiter_pos + 1);
    } 
    else 
    {
        var.nom = ft_strdup(env_line);
        var.valeur = NULL;
    }
    return var;
}

 t_variable *builtin_env(char **env)
{
    int env_count = count_env(env);
    t_variable *env_vars = (t_variable *)malloc(env_count * sizeof(t_variable));

    int i = 0;
    while(i < env_count) 
    {
        env_vars[i] = split_env(env[i]);
        i++;
    }
    return env_vars;
}
char   *my_pwd()
{
    char *buf;
    size_t size;

    char *pwd = getcwd(buf,size); 
    printf("%s\n",pwd);
    return pwd;
}
void    my_echo(int ac,char **av,int t)
{
    int i = 2;

    if (t == 0)
    {
        while (i < ac)
        {
            printf("%s ",av[i]);
            i++;
        }
        printf("\n");
    }
    else
    {
        i = 3;
        while (i < ac)
        {
            printf("%s ",av[i]);
            i++;
        }
    }
}

int main(int ac,char **av,char **env)
{
    int i = 1;
    int t = 0;
//     
    t_variable *my_env = builtin_env(env);
    while(i <= ac - 1)
    {
        if (ft_strcmp(av[i], "pwd") == 0)
            my_pwd();
        if (ft_strcmp(av[1], "env") == 0)
        {
            i = 0;
            while (my_env && my_env[i].nom != NULL && my_env[i].valeur != NULL) 
            {
                printf("%s=%s\n", my_env[i].nom, my_env[i].valeur);
                i++;
            }
        }
        if ((ac > 2 && ft_strcmp(av[1], "echo") == 0) && (ft_strcmp(av[2], "-n") != 0))
        {
            t = 0;
            my_echo(ac,av,t);
            return 0;
        }
        if (( ac > 2 && ft_strcmp(av[1], "echo") == 0) && (ft_strcmp(av[2], "-n") == 0) && av[2]!= NULL)
        {
            t = 1;
            my_echo(ac,av,t);
            return 0;
        }
        if (ft_strcmp(av[1], "cd") == 0)
        {
            builtin_cd(ac,av,my_env);
            return 0;
        }
        i++;
    }
}