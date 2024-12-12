NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address

LIBFT = ./include/libft
SRC = $(wildcard *.c) \
	$(wildcard tokenizer/*.c) \
      $(wildcard builtins/*.c) \
      $(LIBFT)/libft.a
#$(wildcard tokenizer_lv/*.c) 

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
