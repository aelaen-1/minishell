NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT = ./include/libft
SRC = $(wildcard *.c) \
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
    	$(LIBFT)/libft.a

OBJ = $(SRC:.c=.o)

debug: FLAGS += -g
debug: all

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@


$(NAME) :
	make all -C $(LIBFT)
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -lreadline

clean:
	$(RM) $(NAME)
	make clean -C $(LIBFT)
	
fclean: clean	
	$(RM) $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean re all
