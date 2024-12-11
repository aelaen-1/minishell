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
# define PIPE 124
# define UNCLOSED_QUOTE "quote>"
# define UNCLOSED_DOUBLE_QUOTE "dquote>"

typedef enum	e_quoting_status
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quoting_status;

typedef enum e_token_type
{
	NONE,
	WORD,
	BUILTIN,
	STRING,
	DOLLAR,
	LESS, // <
	GREAT, // >
	DLESS, // << 
	DGREAT // >>
}	t_token_type;

typedef struct	s_token
{
	t_token_type type;
	size_t	last_token_length;
	char *value;
}	t_token;

typedef struct s_parse_context
{
	t_token_array   *array;
	t_token	*last_token;
	char	*input;
	int		input_len; 
	size_t		position;
}	t_parse_context;

// growing array
typedef struct s_token_array
{
	t_token **tokens;
	size_t	count; // nb of tokens
	size_t	capacity; // taille obtenue en malloc
}	t_token_array;

/*      envp.c      */
char    *get_path(char *cmd);

/*      exec.c      */
void    exec_cmd(char *cmd);

/*      utils.c     */
void    free_split(char **s);
int     ft_strcmp(char *s1, char *s2);
int		is_space(char c);


/*		tokenizer/	*/
void	print_tokens(char *input);
int		get_next_token(t_parse_context *context, char **err_msg);
int     count_quotes(char *s, int start, char s_or_d);
int     handle_squote(char *s, int *i, t_parse_context *context, char **err_msg);
int 	handle_dquote(char *s, int *i, t_parse_context *context, char **err_msg);

void	init_context(t_parse_context *context, char *input);
int		init_token_array(t_token_array *array);
void	free_token_array(t_token_array *array);
t_token	*add_new_token(t_token_array *array, size_t max_size);


#endif