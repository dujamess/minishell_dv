#include "pipex.h"

void    builtin_echo(int ac,char **av,int t)
{
    int i = 1;

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
        i = 2;
        while (i < ac)
        {
            printf("%s ",av[i]);
            i++;
        }
    }
}