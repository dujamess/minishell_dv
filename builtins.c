#include "pipex.h"
int ft_strcmp(char *s1, char *s2) 
{
    while (*s1 && (*s1 == *s2)) 
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
char	*ft_strdup(char *s)
{
	char			*str;
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	str = malloc(i + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
char      **my_env(char **env)
{
    int i = 0;
    while(env[i])
        i++;
    char **my_env = malloc(sizeof(char *) * i + 1);
    i = 0;
    while(env[i])
    {
        my_env[i] = ft_strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;
    i = 0;
    while(my_env[i])
    {
        printf("%s\n",my_env[i]);
        i++;
    }
    return my_env;
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
    while(i <= ac - 1)
    {
        if (ft_strcmp(av[i], "pwd") == 0)
            my_pwd();
        else if (ft_strcmp(av[i], "env") == 0)
            my_env(env);
        if ((ft_strcmp(av[1], "echo") == 0) && (ft_strcmp(av[2], "-n") != 0))
        {
            t = 0;
            my_echo(ac,av,t);
            return 0;
        }
        if ((ft_strcmp(av[1], "echo") == 0) && (ft_strcmp(av[2], "-n") == 0))
        {
            t = 1;
            my_echo(ac,av,t);
            return 0;
        }
        i++;
    }
}