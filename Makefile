# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/02 23:58:10 by abait-ta          #+#    #+#              #
#    Updated: 2023/09/23 21:50:47 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./Parsing/Tokenizer/lexical_analysis.c ./Parsing/Tokenizer/Linked_list_tools.c ./Parsing/Tokenizer/commande_reform.c \
 ./Parsing/Tokenizer/commande_tokenizer.c ./Parsing/Tokenizer/tokenizer_sequel.c ./Parsing/Tokenizer/tokenizer_accompag_func.c \
Global_main.c ./Parsing/Tokenizer/cleaner_end.c ./Parsing/Tokenizer/cleaner_sequel.c ./Parsing/Tokenizer/token_cleaner.c \
./Parsing/Syntax_analysis/syntax_checker.c ./Parsing/Environnement/env.c
Header = ./Header/Parsing.h

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