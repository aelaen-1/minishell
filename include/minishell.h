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
# include <curses.h>

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define PIPE 124
# define UNCLOSED_QUOTE "quote>"
# define UNCLOSED_DOUBLE_QUOTE "dquote>"
# define DOLLAR 36
# define LESS 60
# define GREAT 62
# define DLESS "<<"
# define DGREAT ">>"

typedef enum e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;
 
typedef struct	s_token
{
	t_token_type type;
	t_builtin	builtin;
	int		is_builtin;
	size_t	length;
	char *value;
}	t_token;

// growing array
typedef struct s_token_array
{
	t_token **tokens;
	size_t	count;
	size_t	capacity;
}	t_token_array;

typedef struct	s_lex_context
{
	char	*input;
	size_t		input_len; 
	size_t		position;
}	t_lex_context;

typedef struct	s_command
{
	// size_t		argc;
	char **argv;
}	t_command;

typedef struct	s_pipeline
{
	size_t		cmd_count;
	t_command	**commands;
}	t_pipeline;

typedef struct	s_program
{
	t_pipeline	*pipeline;
}	t_program;


/*      envp.c      */
char    *get_path(char *cmd);

/*      exec.c      */
void    exec_cmd(char *cmd);

/*      utils.c     */
void    free_split(char **s);
int     ft_strcmp(char *s1, char *s2);
int		is_space(char c);
size_t  eat_spaces(t_lex_context *context);


/*		lexing/	*/
void	init_lex_context(t_lex_context *context, char *input);
int		init_token_array(t_token_array *array);
t_token_array   tokenize_input(char *input);
t_token     *create_token(size_t max_size);
void    append_to_token(t_token *dest, char *src, size_t length);
t_token		*get_next_token(t_lex_context *context);
t_token    *add_token_to_array(t_token_array *array, t_token *token);

int     is_builtin(t_token  *token);
void    find_token_type(t_token *token);

int     count_quotes(char *s, int start, char s_or_d);
int     handle_quote(char *start_quote, t_token *token, t_lex_context *context);

void	print_tokens(t_token_array *tokens);
void	destroy_tokens_array(t_token_array *array);
t_token	*add_new_token(t_token_array *array, size_t max_size);
void    append_to_token(t_token *dest, char *src, size_t length);

t_token    **find_token(t_token **start, t_token **end, t_token_type token_type);
t_command  *parse_command(t_token **start, t_token **end);
t_pipeline  *parse_pipeline(t_token **start, t_token **end);
t_program   *parse_program(t_token_array array);

#endif