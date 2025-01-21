CC = gcc
FLAGS = -Wall -Werror -Wextra
NAME = minishell
LIBFT = include/libft
HEADER = include/minishell.h
OBJ_PATH = objs

SOURCES = $(wildcard *.c) \
        $(wildcard lexing/*.c) \
        $(wildcard tools/*.c) \
        $(wildcard expansions/*.c) \
        $(wildcard parsing/*.c) \
        $(wildcard exec/*.c) \
        $(wildcard env_variables/*.c) \
        $(wildcard history/*.c) \
        $(wildcard init/*.c) \
        $(wildcard pipes/*.c) \
        $(wildcard redirections/*.c) \
        $(wildcard signals/*.c) \
        $(wildcard builtins/*.c) \
        $(wildcard free/*.c)

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