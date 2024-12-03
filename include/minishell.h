#ifndef MINISHELL_H
 #define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

/*      envp.c      */
char    *get_path(char *cmd);

/*      exec.c      */
void    exec_cmd(char *cmd);

/*      utils.c     */
void    free_split(char **s);
int     ft_strcmp(char *s1, char *s2);

#endif