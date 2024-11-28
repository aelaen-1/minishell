NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC = builtins/

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.c
    $(CC) $(FLAGS) -o $@ -c $<
$(NAME): %.o
    $(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean: $(OBJ)
    $(RM) $(OBJ)

fclean: clean
    $(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
