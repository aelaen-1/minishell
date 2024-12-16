#include "include/minishell.h"

void	tokenizer(char *input)
{
    t_parse_context context;
    t_token         *last_token;
    
    if(!init_token_array(&context.array))
        return ;
    init_context(&context, input);
    while (context.position < context.input_len)
    {
        last_token = get_next_token(&context);
        printf("%s\n", last_token->value);
    }
    t_command *first_cmd = get_next_command(&context.array);
    size_t i = 0;
    while(first_cmd->cmd_with_args[i] != NULL)
    {
        printf("%s\n", first_cmd->cmd_with_args[i]);
        i++;
    }
    destroy_tokens_array(&context.array);
}

t_command   *get_next_command(t_token_array *array)
{
    t_command   *next_cmd = malloc(sizeof(t_command));
    size_t      i;
    size_t      j;

    i = 0;
    j = 0;
    while(strcmp(array->tokens[i]->value, "|") && array->tokens[i])
    {
        next_cmd->cmd_with_args[j] = array->tokens[i]->value;
        i++;
        j++;
    }
    return (next_cmd);
}

// REPL
int main (int ac, char **av)
{
    (void)ac;
    (void)av;
    while(1)
    {
        char *cmd = readline("minishell % ");
        tokenizer(cmd);
    }
    return 0;
}   