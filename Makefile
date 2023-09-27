# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/02 23:58:10 by abait-ta          #+#    #+#              #
#    Updated: 2023/09/27 21:33:51 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./Parsing/Lexical_analysis/lexical_analysis.c ./Parsing/Lexical_analysis/Linked_list_tools.c ./Parsing/Lexical_analysis/commande_reform.c \
 ./Parsing/Lexical_analysis/commande_tokenizer.c ./Parsing/Lexical_analysis/tokenizer_sequel.c ./Parsing/Lexical_analysis/tokenizer_accompag_func.c \
Global_main.c ./Parsing/Lexical_analysis/cleaner_end.c ./Parsing/Lexical_analysis/cleaner_sequel.c ./Parsing/Lexical_analysis/token_cleaner.c \
./Parsing/Syntax_analysis/syntax_checker.c ./Parsing/Environnement/env_expansion.c ./Parsing/Environnement/env_builder.c \
./Parsing/Syntax_analysis/syntax_outfunction.c 

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