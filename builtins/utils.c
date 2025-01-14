#include "../include/minishell.h"

char *key_value_join(char *key , char *value)
{
    char *buffer;
    char *out;

    if(!key || !value)
        return NULL;
    buffer = ft_strjoin(key,"=");
    out = ft_strjoin(buffer , value);
    free(buffer);
    return (out);
}
t_env_node *init_env(char **env)
{
    t_env_node *top;
    t_env_node *bottom;
    t_env_node *new_node;
    int i;

    top = NULL;
    bottom = NULL;
    new_node = NULL;
    i = 0;
    while(env[i])
    {
        new_node = malloc(sizeof(t_env_node));
        if(!new_node)
            return (free(new_node), NULL);
        new_node->env_var = ft_strdup(env[i]);
        if(!new_node->env_var)
            return (free(new_node), NULL);
        new_node->next = NULL;
        new_node->previous = bottom;
        if(!top)
            top = new_node;
        else
            bottom->next = new_node;
        bottom = new_node;
        i++;
    }
    return top;
}

int update_env(t_env_node **env , char *key, char *value)
{
    t_env_node *loop;
    t_env_node *new_node;

    if(!key || !value)
        return 0;
    loop = *env;
    while(loop)
    {
         if (ft_strncmp(loop->env_var, key, strlen(key)) == 0)
         {
            free(loop->env_var);
            loop->env_var = key_value_join(key, value);
            return 1;
         }
         if (!loop->next)
            break;
         loop = loop->next;
    }

    new_node = malloc(sizeof(t_env_node));
    if(!new_node)
        return 1;

    new_node->env_var = key_value_join(key, value);
    if(!new_node->env_var)
        return (free(new_node),2);
    new_node->next = NULL;
    new_node->previous = loop;
    if(loop)
        loop->next = new_node;
    else 
        *env = new_node;
    return 3;
}

int unset_env(t_env_node **env, char *key)
{
    t_env_node *loop;

    loop = *env;

    while(loop)
    {
        if (ft_strncmp(loop->env_var, key, strlen(key)) == 0)
        {
            if(loop->previous)
                loop->previous->next = loop->next;
            else 
                *env = loop->next;
            if(loop->next)
                loop->next->previous = loop->previous;
            free(loop->env_var);
            free(loop);
            return 1;
        }
        loop = loop->next;
    }
    return 0;
}