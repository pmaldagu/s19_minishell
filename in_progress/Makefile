# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agossuin <agossuin@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/09 17:27:22 by agossuin          #+#    #+#              #
#    Updated: 2020/04/09 17:35:49 by agossuin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAMES	=	cmd.c \
				dup.c \
				env.c \
				get.c \
				istype.c \
				minishell.c \
				prompt.c \
				get_redir.c

SRC			=	$(addprefix srcs/, $(SRC_NAMES))
OBJ			=	$(SRC:%.c=%.o)

NAME		=	minishell
LIBFT		=	libft/libft.a

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
AR			=	ar -rc

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) -o $(NAME) $(OBJ) $(LIBFT)
			make clean

test:		all
			./minishell
clean:
			cd libft/ && make $@
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(LIBFT)
			$(RM) $(NAME)

re:			fclean all

$(LIBFT):
			cd libft/ && make bonus
