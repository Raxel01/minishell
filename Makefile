SRC = ./Parsing/lexical_analysis.c

Header = ./Header/header.h

CFLAGS = -Wall -Wextra -Werror


INCLUDES= -I/goinfre/$(USER)/homebrew/opt/readline/include

READLINE= -lreadline -L/goinfre/$(USER)/homebrew/opt/readline/lib

NAME = Minishell

CC = cc

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME): $(HEADER) $(OBJ)
	@$(CC)  $(READLINE) -o  $@  $(OBJ) 

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@	

clean :
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

norm :
		norminette

.PHONY: clean fclean all re NAME