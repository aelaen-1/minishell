#include "include/minishell.h"

int is_space(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int ft_strcmp(char *s1, char *s2)
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
    s = NULL;
}