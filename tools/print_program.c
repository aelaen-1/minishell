#include "../include/minishell.h"

// D'abord telecharger l'outil de visualisation : sudo apt install graphviz
// creer un fichier
// 1 - ./minishell --pp 2> nom_du_fichier
// 2 - dot -Tpng -o nom_pour_l_image_generee.png nom_du_fichier

void    print_command_to_dot(t_command *command)
{
    size_t  i;
    i = 1;
    fprintf(stderr,"\"%p\" [label = \"%s\"]\n", command, command->argv[0]);
    while (command->argv[i])
    {
        fprintf(stderr, "\"%p\" -> \"%p\"\n", command, command->argv + i);
        fprintf(stderr,"\"%p\" [label = \"%s\"]\n", command->argv + i, command->argv[i]);
        i++;
    }
}
void    print_pipeline_to_dot(t_pipeline *pipeline)
{
    fprintf(stderr,"\"%p\" [label = \"pipeline\"]\n", pipeline);
    size_t i = 0;
    while (i < pipeline->cmd_count)
    {
        fprintf(stderr, "\"%p\" -> \"%p\"\n", pipeline, pipeline->commands[i]);
        print_command_to_dot(pipeline->commands[i]);
        i++;
    }
}

void    print_program_to_dot(t_program  *program)
{
    fprintf(stderr,"strict digraph {\n");
    fprintf(stderr,"\"%p\" [label = \"program\"]\n", program);
    fprintf(stderr, "\"%p\" -> \"%p\"\n", program, program->pipeline);
    print_pipeline_to_dot(program->pipeline);
    fprintf(stderr,"}\n");
}
//  to add in main
    // if (ac == 2 && !strcmp(av[1], "--pp"))
    // {
    //     while (1)
    //     {
    //     char *input = readline("minishell % ");
    //     t_token_array tokens = tokenize_input(input);
    //     t_program *program = parse_program(tokens, envp);
    //     print_program_to_dot(program);
    //     destroy_tokens_array(&tokens);
    //     }
    //     return 0;
    // }