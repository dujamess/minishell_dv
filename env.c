#include "pipex.h"

int count_env(char **env) 
{
    int count = 0;
    while (env[count]) 
        count++;
    return count;
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