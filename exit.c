#include "pipex.h"


void    builtin_exit(char *av)
{
    if (av == NULL)
        exit(0);
    int i;
    i = 0;
    if (i == 0 && av[i] == '0' && av[i+1] == '\0')
        exit(0);
}