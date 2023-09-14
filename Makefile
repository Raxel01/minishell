# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/02 23:58:10 by abait-ta          #+#    #+#              #
#    Updated: 2023/09/14 19:45:00 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./Parsing/lexical_analysis.c ./Parsing/Linked_list_tools.c ./Parsing/commande_reform.c \
 ./Parsing/commande_tokenizer.c ./Parsing/tokenizer_sequel.c ./Parsing/tokenizer_accompag_func.c \
Global_main.c

Header = ./Header/Parsing_Header.h

CFLAGS = -Wall -Wextra -Werror

# INCLUDES= -I/goinfre/$(USER)/homebrew/opt/readline/include

READLINE = -lreadline 

# -L/goinfre/$(USER)/homebrew/opt/readline/lib

NAME = Minishell

CC = cc

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME): $(HEADER) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ -fsanitize=address -g  $(OBJ)  $(READLINE) && rm -rf $(OBJ)

%.o : %.c $(HEADER)
	@$(CC)  $(CFLAGS) -c -fsanitize=address -g $< -o  $@	

clean :
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

norm :
		norminette

.PHONY: clean fclean all re NAME