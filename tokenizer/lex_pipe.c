#include "../include/minishell.h"

//              PIPE
// int space_before_pipe(char *s, int *i, t_parse_context *context)
// {
//     // if (s[i] == PIPE)
//     int j = 0;
//     int index = *i;
//     if (s[index - 1] && !is_space(s[index - 1]))
//         return (0); // the last token isn't the pipe
//     else if (s[index - 1] && is_space(s[index - 1]))
//     {
//         context->last_token[j] = PIPE;
//         return (1);
//     }
//     context->last_token[j] = PIPE;
//     return (-1);
// }
// else if (s[i] == PIPE)
// {
//     if((space_before_pipe(s, &i, context) == 1) != 0)
//     {
//         context->last_token[j] = s[i];
//         return(context->last_token[++j] = 0, i + 1);
//     }
//     else
//         return(context->last_token = 0, i);
// }
