#include "../include/minishell.h"

int builtin_unset(t_command *command)
{
    if(!command->argv[1])
        return (write(1,"unset: not enough arguments\n",28),1);
    else
        unset_env(&command->envp, command->argv[1]);
    return 0;
}