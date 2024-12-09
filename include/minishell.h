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

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define UNCLOSED_QUOTE "quote>"
# define UNCLOSED_DOUBLE_QUOTE "dquote>"

typedef enum e_type
{
	CMD,
	IN_REDIRECT,
	OU_REDIRECT,
	PIPE,
	DONT_EXIST
}	t_type;

typedef enum e_builtins
{
	CD,
	// ECHO,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtins;

typedef struct s_exec
{
	char			**cmd;
	char			**in;
	int				fdin;
	int				is_fdin;
	char			**out;
	int				fdout;
	int				is_fdout;
	int				builtin;
	struct s_exec	*next;
}	t_exec;

typedef struct s_token
{
	char			**global;
	t_type			data_type;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	char		*currentpath;
	struct stat	dossier;
	char		*userstr;
	char		*user;
	char		*input;
	t_list		*env;
	uint8_t		exitstatus;
	char		**tabenv;
	char		**tabcmd;
	int			exe_n;
	int			exe_size;
	pid_t		*pid;
	int			*pipe;
	int			pipe_n;
	int			clear_fd[2];
	t_token		*lst;
	t_exec		*exe;
}	t_mini;

typedef struct parse_context
{
	char *last_token;
}	t_parse_context;

/*      envp.c      */
char    *get_path(char *cmd);

/*      exec.c      */
void    exec_cmd(char *cmd);

/*      utils.c     */
void    free_split(char **s);
int     ft_strcmp(char *s1, char *s2);
int		is_space(char c);


void	print_tokens(char *input);
int		get_next_token(char *s, struct parse_context *context, char **err_msg);


#endif