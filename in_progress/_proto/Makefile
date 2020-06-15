SRCS = ./srcs/*.c

LIBFT = ./libft/libft.a

OBJS = *.o

CC = gcc

FLAG = -Wall -Wextra -Werror

NAME = minishell

all:
	make -C ./libft
	$(CC) -o $(NAME) $(FLAG) $(SRCS) $(LIBFT) main.c

clean:
	make -C ./libft clean
	rm -rf $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

test: re
	./$(NAME)

.PHONY: all clean fclean test re
