#include "minishell.h"

int count_env(char **env) 
{
    int count = 0;
    while (env[count]) 
        count++;
    return count;
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
    t_variable *env_vars = (t_variable *)malloc((env_count + 1) * sizeof(t_variable));

    int i = 0;
    while(i < env_count)
    {
        env_vars[i] = split_env(env[i]);
        i++;
    }
    env_vars[i].nom = NULL;
    env_vars[i].valeur = NULL;
    return env_vars;
}