# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/02 23:58:10 by abait-ta          #+#    #+#              #
#    Updated: 2023/11/11 20:01:31 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./Parsing/Lexical_analysis/lexical_analysis.c ./Parsing/Lexical_analysis/Linked_list_tools.c \
 ./Parsing/Lexical_analysis/commande_reform.c ./Parsing/Lexical_analysis/commande_tokenizer.c \
 ./Parsing/Lexical_analysis/tokenizer_sequel.c ./Parsing/Lexical_analysis/tokenizer_accompag_func.c \
Global_main.c ./Parsing/Lexical_analysis/cleaner_end.c ./Parsing/Lexical_analysis/cleaner_sequel.c \
./Parsing/Environnement/env_expansion.c ./Parsing/Environnement/env_builder.c ./Parsing/Data_sender/here_docbuilder.c \
./Parsing/Syntax_analysis/syntax_outfunction.c ./Parsing/Data_sender/itoa.c \
./Parsing/Lexical_analysis/out_function.c ./Parsing/Data_sender/List_management.c ./Parsing/Data_sender/linked_list_tools.c \
./Parsing/Data_sender/recognizer.c ./Parsing/Data_sender/command_table.c ./Parsing/Data_sender/fd_generator.c \
./Parsing/Lexical_analysis/token_cleaner.c ./Parsing/Syntax_analysis/syntax_checker.c ./Parsing/Data_sender/heredoc_helper.c\
./Built-in/cd.c ./Built-in/env_displayer.c ./Built-in/exit.c ./Built-in/export.c ./Built-in/pwd.c \
./Built-in/unset.c ./Built-in/echo.c ./Built-in/builtin_recognizer.c Global_outfunc.c ./Built-in/exported_var.c \
./Built-in/exportmodify_mode.c ./Built-in/exportaddmember_mode.c \
./execution/execution.c ./execution/utils.c ./execution/paths.c ./execution/libft.c ./execution/buildexec_env.c \
./execution/processes.c

Header = ./Header/Parsing.h ./Header/execution.h

CFLAGS = -Wall -Wextra -Werror 

INCLUDES= -I ~/.brew/opt/readline/include

READLINE= -lreadline -L ~/.brew/opt/readline/lib

NAME = Minishell

CC = cc

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME): $(Header) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ)  -o    $(NAME) $(READLINE)
%.o : %.c $(Header)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
clean :
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all

norm :
		norminette
succes :
		make re && ./Minishell
.PHONY: clean fclean all re NAME