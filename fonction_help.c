#include "minishell.h"

void	free_d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	unsigned int	k;
// 	unsigned int	some;
// 	char			*s3;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	some = ft_strlen(s1) + ft_strlen(s2);
// 	s3 = malloc(sizeof(char) * (some +1));
// 	if (!s3)
// 		return (NULL);
// 	while (s1[i] && i < some)
// 		s3[j++] = s1[i++];
// 	while (s2[k] && j < some)
// 		s3[j++] = s2[k++];
// 	s3[j] = '\0';
// 	return (s3);
// }
