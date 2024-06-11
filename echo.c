#include "minishell.h"

void    builtin_echo(int ac,char **av)
{
    int i;
    (void)ac;
    i = 0;
    if (ft_strcmp(av[1],"-n") == 0)
    {
        while(av[i] && ft_strcmp(av[i],"-n") == 0)
            i++;
        while(av[i])
        {
            printf("%s ",av[i]);
            i++;
        }
    }
    else
    {
        i = 0;
        while(av[i])
        {
            printf("%s ",av[i]);
            i++;
        }
        printf("\n");
    }
}