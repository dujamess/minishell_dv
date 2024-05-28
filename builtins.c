#include "pipex.h"
char   *my_pwd();
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
char *ft_strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i]) 
    {
        dest[i] = src[i];
        i++;
    }
    dest[i]= '\0';
    return dest;
}

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0') 
    {
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return dest;
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}
char      **my_env(char **env,t_variable *var)
{
    int i = 0;
    while(env[i])
        i++;
    var->OLDPWD = NULL;
    var->PWD = NULL;
    char **my_env = malloc(sizeof(char *) * i + 1);
    i = 0;
    char *pwd = my_pwd();
    char *path_pwd = ft_strcat_total("PWD=", pwd);

    while(env[i])
    {
        if(env[i][0] == 'P' && env[i][1] == 'W')
        {
            var->PWD = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
            var->PWD = ft_strcpy(var->PWD,env[i]);
        }
        if(env[i][0] == 'O' && env[i][1] == 'L')
        {
            var->OLDPWD = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
            var->OLDPWD = ft_strcpy(var->OLDPWD,env[i]);
        }
        my_env[i] = ft_strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;
    i = 0;
    while(my_env[i])
        printf("%s\n",my_env[i++]);
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

void    my_cd(char *av)
{
    if (chdir(av) == 0)
        printf("suces\n");
    else
        printf("error\n");
}
int main(int ac,char **av,char **env)
{
    int i = 1;
    int t = 0;
    t_variable  *var = malloc(sizeof(t_variable));
    while(i <= ac - 1)
    {
        if (ft_strcmp(av[i], "pwd") == 0)
            my_pwd();
        else if (ft_strcmp(av[1], "env") == 0)
            my_env(env,var);
        // else if (ft_strcmp(av[1], "bash") == 0)
        //     my_env(env,var);
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
            my_cd("/home/khadija/Desktop/minishel_dv/home");
            return 0;
        }
        i++;
    }
}