#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <errno.h>

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

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_token
{
	t_token_type	type;
	size_t			length;
	char			*value;
}	t_token;

typedef struct s_token_array
{
	t_token		**tokens;
	size_t		count;
	size_t		capacity;
}	t_token_array;

typedef struct s_lex_context
{
	char		*input;
	size_t		input_len;
	size_t		position;
}	t_lex_context;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
}	t_redir;

typedef struct s_env_node
{
	char				*env_var;
	bool			is_exported;
	struct s_env_node	*next;
	struct s_env_node	*previous;
}	t_env_node;

typedef struct s_command
{
	char		**argv;
	t_env_node	*envp;
	int			fds[2];
	t_redir		redir_in;
	t_redir		redir_out;
}	t_command;

typedef struct s_pipeline
{
	size_t		cmd_count;
	t_command	**commands;
}	t_pipeline;

typedef struct s_context
{
	int	last_cmd_status;
	t_env_node	*envp;	
}	t_context;

typedef struct s_program
{
	t_pipeline	*pipeline;
	int			last_cmd_status;
}	t_program;

/*      exec      */
void			execute_program(t_program *program, t_context *context);

int				is_builtin(t_command *cmd);
int				handle_builtin_commands(t_command *cmd, t_context *context);

t_env_node	*create_env_node(char *env_var, t_env_node *bottom);
char			**lst_to_char(t_env_node *top); // used to pass env to execve

int				*malloc_pids(t_pipeline *pipeline);
int				**malloc_fds(t_pipeline *pipeline);
void			free_fds(int **fds, size_t	command_count);
// error_msg.c
void			command_not_found_and_exit(char *arg, char *path, char **env, int *free_path);

/*      utils/     */
void			free_split(char **s);
int				ft_strcmp(char *s1, char *s2);
int				is_space(char c);
size_t			eat_spaces(t_lex_context *context);
size_t			get_number_length(int n);

t_quote_type	*get_quote_state(char *s);
void			remove_quotes(t_command *cmd);


/*		lexing/	*/
void			init_lex_context(t_lex_context *context, char *input);
int				init_token_array(t_token_array *array);
t_token_array	tokenize_input(char *input);
t_token			*create_token(size_t max_size);
void			append_to_token(t_token *dest, char *src, size_t length);
t_token			*get_next_token(t_lex_context *context);
t_token			*add_token_to_array(t_token_array *array, t_token *token);

void			find_token_type(t_token *token);

int				count_quotes(char *s, int start, char s_or_d);
int				handle_quote(char *start_quote, t_token *token,
					t_lex_context *context);
void			remove_quotes(t_command *cmd);

void			print_tokens(t_token_array *tokens);
void			destroy_tokens_array(t_token_array *array);
void			append_to_token(t_token *dest, char *src, size_t length);

/*		parsing/		*/
t_command		*parse_command(t_token **start, t_token **end);
t_command		*create_command(int argc);
void			close_command_fds(t_command *command);
void			destroy_command(t_command *command);
t_pipeline		*parse_pipeline(t_token **start, t_token **end);
t_program		*parse_program(t_token_array array);
int				parse_redir(t_command *cmd, t_token **current);

size_t			get_expanded_arg_size(char *command_arg, t_context *context, t_quote_type *quoting);
void			expand_command(t_command *command, t_context *context);
void			redirect_command(t_command *command);
		
// outil pour print le prgram
void			print_pipeline_to_dot(t_pipeline *pipeline);
void			print_command_to_dot(t_command *command);
void			print_program_to_dot(t_program *program);

/*		builtins/		*/
t_env_node		*init_env(char **env);
int				update_env(t_env_node **env, char *key, char *value);
int				unset_env(t_env_node **env, char *key);
char			*get_env_value(char *to_find, t_env_node *envp);
char			*key_value_join(char *key, char *value);
int				is_valid_identifier(char *arg);

int				builtin_echo(t_command *command, t_context *context);
int				builtin_env(t_command *command, t_context *context);
int				builtin_pwd(t_command *command, t_context *context);
int				builtin_cd(t_command *command, t_context *context);
int				builtin_export(t_command *command, t_context *context);
int				builtin_unset(t_command *command, t_context *context);

void			free_program( t_env_node *envp);
void			free_pipeline(t_pipeline *pipeline);
void			signal_handler();

/*		free/		*/
void			free_command_argv(char **cmd_arg);




#endif