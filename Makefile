SRC=			./line_process.c \
			./main.c \

OBJ=			 $(SRC:.c=.o)

NAME=			 a.out

CFLAGS=			-Wall -Wextra -Werror -ansi -pedantic -g3

all:			$(NAME)

$(NAME):		$(OBJ)
	gcc -o $(NAME) $(OBJ) -g3

clean:
	rm -f $(OBJ)

fclean:			clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
