CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CC = cc
SRC = pipex.c fonction_help.c split.c process.c

OBJECT = $(SRC:.c=.o)
NAME = pipex
all : $(NAME)
$(NAME) :$(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)
%o : %c
	$(CC) $(CFLAGS) -c $< -$@

clean :
		rm -rf $(OBJECT)
fclean :clean
		rm -rf $(NAME)
re : fclean all