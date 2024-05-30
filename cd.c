#include "pipex.h"
t_variable  *check_variable(t_variable *my_env,char *variable)
{
    int i;

    i = 0;
    while(my_env[i].nom)
    {
        if(ft_strcmp(my_env[i].nom,variable) == 0)
            return (&my_env[i]);
        i++;
    }
    return NULL;
}
int    builtin_cd(int ac,char **av,t_variable *my_env)
{
    char *oldpwd = getcwd(NULL, 4096);
    char  *pwd;
    t_variable *path;
    t_variable *pwd_env;
    int t;
    if(ac == 1)
    {
        path = check_variable(my_env,"HOME");
        if(path == NULL)
            printf("variable HOME non trouver dans votre env\n");
        int t = chdir(path->valeur);
        pwd_env= check_variable(my_env,"PWD");
        if (pwd_env)
        {
            pwd = getcwd(NULL, 4096);
            if (!pwd)
                return 0;
            free(pwd_env->valeur);
            pwd_env->valeur = pwd;
        }
        pwd_env = check_variable(my_env,"OLDPWD");
        if (pwd_env)
        {
            if (!oldpwd)
                return 0;
            free(pwd_env->valeur);
            pwd_env->valeur = oldpwd;
        }
    }
    else
    {
        if(access(av[1],F_OK) != 0 ||access(av[1],X_OK) != 0 )
            printf("%s : not directory \n",av[1]);
        else
        {
            chdir(av[1]);
            pwd = getcwd(NULL, 4096);
            pwd_env= check_variable(my_env,"PWD");
            pwd_env->valeur = pwd;
            pwd_env = check_variable(my_env,"OLDPWD");
            pwd_env->valeur = oldpwd;
        }
    }
    // int i = 0;
    // while (my_env && my_env[i].nom != NULL && my_env[i].valeur != NULL) 
    // {
    //     printf("%s=%s\n", my_env[i].nom, my_env[i].valeur);
    //     i++;
    // }
}