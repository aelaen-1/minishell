#include "include/minishell.h"

int     ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void free_split(char **s)
{
    int i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
    s = NULL; // obligatoire ? 
}