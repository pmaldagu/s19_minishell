SRC_NAMES	=	builtin/cd.c \
				builtin/echo.c \
				builtin/pwd.c \
				builtin/unset.c \
				builtin/env.c \
				builtin/exit.c \
				builtin/export.c \
				../main.c \
				parser.c \
				traduction.c \
				tools.c \
				lexer.c \
				lexer_annexe.c \
				exec.c \
				variable.c \
				path.c \
				ft_atoll.c \
				redirection.c \
				interpolation.c \
				error.c \
				quotes.c \
				pipe.c \
				init.c \
				errexec.c \
				remove_dir.c \
				free.c \
				syntax_error.c

SRC			=	$(addprefix src/, $(SRC_NAMES))
OBJ			=	$(SRC:%.c=%.o)

NAME		=	minishell
LIBFT		=	./libft/libft.a

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
AR			=	ar -rc

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
			make clean

test:		all
			./minishell -c

clean:
			cd ./libft/ && make $@
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(LIBFT)
			$(RM) $(NAME)

re:			fclean all

$(LIBFT):
			cd ./libft/ && make bonus
