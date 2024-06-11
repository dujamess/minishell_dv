#include "minishell.h"


void heredoc(char *av) 
{
    pid_t t;
    char line[1024];
    ssize_t bytes_read;
    t = fork();
    if (t == 0) 
    {
        write(1,"> ",2);
        while ((bytes_read = read(STDIN_FILENO, line, sizeof(line))) > 0) 
        {
            if (strncmp(line, av,ft_strlen(av)) == 0 && line[ft_strlen(av)] == '\n') 
                exit(1);
            write(1,"> ",2);
        }
    } 
    else
        wait(NULL);
}