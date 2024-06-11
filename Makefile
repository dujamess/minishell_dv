CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CC = cc
SRC = cd.c env.c exit.c fonction_help.c minishell.c \
	  pwd.c unset.c builtins_util.c echo.c execution.c export.c split.c SHLVL.c here_doc.c

OBJECT = $(SRC:.c=.o)
NAME = minishell
all : $(NAME)
$(NAME) :$(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME) -lreadline
%o : %c
	$(CC) $(CFLAGS) -c $< -$@

clean :
		rm -rf $(OBJECT)
fclean :clean
		rm -rf $(NAME)
re : fclean all