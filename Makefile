CC = gcc
FLAGS = -Wall -Werror -Wextra
NAME = minishell
LIBFT = include/libft
HEADER = include/minishell.h
OBJ_PATH = objs

SOURCES =      main.c \
                lexing/lexer.c \
                lexing/init_array_and_context.c \
                lexing/lexing_utils.c \
                lexing/quotes.c \
                lexing/token_array.c \
                tools/utils.c \
                expansions/calculate_expanded_sizes.c \
                expansions/expansion.c \
                expansions/expansion_2.c \
                expansions/expansion_utils.c \
                expansions/quote_removal.c \
                parsing/parse_command.c \
                parsing/parse_pipelines.c \
                parsing/parse_redir.c \
                parsing/parser.c \
                parsing/pipeline_utils.c \
                parsing/redirection.c \
                parsing/heredoc.c \
                exec/builtins_and_pids.c \
                exec/exec.c \
                exec/exec_utils.c \
                exec/exec_error.c \
                exec/exec_error_2.c \
                exec/fork.c \
                builtins/change_dir.c \
                builtins/echo.c \
                builtins/env.c \
                builtins/exit.c \
                builtins/export.c \
                builtins/export_utils.c \
                builtins/print_working_directory.c \
                builtins/unset.c \
                builtins/utils.c \
                builtins/utils_env.c \
                free/free.c \
                signals/signals.c

OBJS = $(patsubst %.c,$(OBJ_PATH)/%.o,$(SOURCES))

all: lib $(NAME)

debug: FLAGS += -g
debug: all

lib:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -L $(LIBFT) -o $(NAME) $(OBJS) -lft -lreadline

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT)

re: fclean all

.PHONY: all lib clean fclean re
