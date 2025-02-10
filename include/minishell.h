/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:06:11 by glabaden          #+#    #+#             */
/*   Updated: 2025/02/10 13:48:00 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	bool				is_exported;
	struct s_env_node	*next;
	struct s_env_node	*previous;
}	t_env_node;

typedef struct s_command
{
	char				**argv;
	t_env_node			*envp;
	int					fds[2];
	size_t				index;
	t_redir				redir_in;
	t_redir				redir_out;
	struct s_pipeline	*pipeline;
}	t_command;

typedef struct s_pipeline
{
	size_t		cmd_count;
	t_command	**commands;
}	t_pipeline;

typedef struct s_context
{
	int			last_cmd_status;
	t_env_node	*envp;	
}	t_context;

typedef struct s_program
{
	t_pipeline	*pipeline;
	int			last_cmd_status;
}	t_program;

typedef struct s_arg_expansion_state
{
	char			*res;
	size_t			size;
	size_t			i;
	size_t			j;
	size_t			len;
	t_quote_type	*quoting;
}	t_arg_expansion_state;

/*      exec      */
int				execute_program(t_program *program, t_context *context);

int				is_builtin(t_command *cmd);
int				handle_builtin_commands(t_command *cmd, t_context *context);

t_env_node		*create_env_node(char *env_var, t_env_node *bottom);
char			**lst_to_char(t_env_node *top); // used to pass env to execve
char			*get_path(t_command *cmd, t_env_node *envp);
int				*malloc_pids(t_pipeline *pipeline);
int				exec_builtin(t_command *cmd, t_context *context);
int				do_fork(t_command *cmd, int *pid, char *path,
					t_context *context);

/*      utils/     */
void			free_split(char **s);
int				ft_strcmp(char *s1, char *s2);
int				is_space(char c);
size_t			eat_spaces(t_lex_context *context);
size_t			get_number_length(int n);

t_quote_type	*get_quote_state(char *s);
void			remove_quotes(t_command *cmd);

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

void			destroy_tokens_array(t_token_array *array);
void			append_to_token(t_token *dest, char *src, size_t length);

int				is_quote(char c);
int				is_pipe_or_redir(char c);
int				is_double_redir(char c, char d);

/*		parsing/		*/
t_command		*parse_command(t_token **start, t_token **end);
t_command		*create_command(size_t argc);
void			close_command_fds(t_command *command);
void			destroy_command(t_command *command);
t_pipeline		*parse_pipeline(t_token **start, t_token **end, t_context *context);
t_program		*parse_program(t_token_array array, t_context *context);
int				parse_redir(t_command *cmd, t_token **current,
					t_token **last_token, t_token **cmd_start);

size_t			get_expanded_arg_size(char **command_arg,
					t_context *context, t_quote_type *quoting);
int				is_expandable_dollar(char c, char d, char quoting);
size_t			get_var_len(char *arg);
void			expand_command(t_command *command, t_context *context);
void			expand_last_cmd_status(char *var_value, char *res,
					size_t *j, size_t *i);
void			remove_null_commands(t_command *command);
int				redirect_command(t_command *command);
bool			init_arg_expansion_state(t_arg_expansion_state *vars,
					t_context *context, char *arg);
bool			try_expand_status(char c, t_context *context,
					t_arg_expansion_state *vars);

t_pipeline		*free_pipeline_on_pipe_failure(t_pipeline *pipeline,
					size_t *i);
int				check_if_pipeline_error(t_token **start, t_token **end,
					size_t cmd_count, t_context *context);

/*		builtins/		*/
t_env_node		*init_env(char **env);
int				update_env(t_env_node **env, char *key, char *value);
int				unset_env(t_env_node **env, char *key);
char			*get_env_value(char *to_find, t_env_node *envp);
char			*key_value_join(char *key, char *value);
int				is_valid_identifier(char *arg);
void			*create_export_node(t_env_node *env, char *key, char *value);
int				check_if_exported(char *arg, t_context *context);
void			export_key_without_value(char *key, t_context *context);
int				exec_permission(char *cmd, t_context *context,
					struct stat path_stat);

int				builtin_echo(t_command *command);
int				builtin_env(t_command *command, t_context *context);
int				builtin_pwd(t_command *command);
int				builtin_cd(t_command *command, t_context *context);
int				builtin_export(t_command *command, t_context *context);
int				builtin_unset(t_command *command, t_context *context);

void			free_program( t_program *program);
void			free_pipeline(t_pipeline *pipeline);
void			signal_handler(void);
void			ctrlc_exit_status(t_context *context);
int				builtin_exit(t_command *command, t_context *context);
/*		free/		*/
void			free_command_argv(char **cmd_arg);
void			free_env_node(t_env_node *node);

// nouvelles fonctions
int				handle_exec_error(char *cmd, t_context *context);
void			update_command_status(size_t *i, int ret, t_context *context);
void			update_status_out(int ret, t_context *context);
void			handle_ctrlc_exec(int sig);
void			handle_ctrlc(int sig);
void			handle_sig_quit(int sig);
void			wait_children(int *pids, t_context *context, t_program *p);
int				handle_heredoc(t_command *command);
int				return_exec(int ret_exec, t_program *program,
					t_context *context, int *pids);

#endif
