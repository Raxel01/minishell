/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_Header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:14:30 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/14 16:19:17 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>

typedef struct commande
{
	char				*commande;
}						t_commande;

typedef struct variable
{
	int					i;
	int					flg;
	char				*epured_string;
	char				*begin;
}						t_var;

typedef struct details
{
	void				*commande;
	void				*option;

}						t_data_details;

/*SPECIAL_vAR IN SHELL LIKE : $1 $0..$?..$$.*/
enum					e_token_type
{
	WORD,
	A_SPACE,
	PIPE,
	OUT_REDIR,
	IN_REDIR,
	ENV_VAR,
	SPECIAL_VAR,
	HERE_DOC,
	APPEND_SYM
};
enum					e_token_state
{
	NORMAL,
	IN_SQUOT,
	IN_DQUOT
};

typedef struct start_end_geter
{
	int start;
	int end;
	int flag;
	int	node_member;
}	t_pos_get;

typedef struct token_list
{
	char				*token;
	enum e_token_type	type;
	enum e_token_state	state;
	int					index;
	int 				node_member;
	struct token_list	*next;
	struct token_list	*prev;
}						t_token_list;

typedef struct tree
{
	void				*data;
	enum e_token_state	state;
	struct tree			*left;
	struct tree			*right;
}						t_trees;
/*will may add messages option {}*/
/****************EPUR_STRING : COMMANDE CLEANER ***********************/
char					*epur_string(char *commande);
int						epur_len_helper(char *commande);
int						word_epur_helper(char *commande);
/************************************************************************/
/*******************LINKED LIST FUNCTION*********************************/
t_token_list			*build_new_token_node(char *token_data,
							enum e_token_type type, enum e_token_state state);
void					add_tokens_to_list(t_token_list **token,
							t_token_list *next_token);
void					print_tokens(t_token_list **begin);
void					free_token_list(t_token_list **head);
/************************************************************************/
/*************************TOKENIZER =>TOOLS******************************/
t_token_list			*lexical_analysis(char *commande);
char					*lexems_finder(char *commande, t_token_list **token);
int						quoted_symbole(char c);
char					*get_t_word_token(char *commande, t_token_list **token,
							enum e_token_type t_type,
							enum e_token_state s_token);
char					*get_space_token(char *commande, t_token_list **token,
							enum e_token_type t_type,
							enum e_token_state s_token);
char					*get_pipe_token(char *commande, t_token_list **token,
							enum e_token_type t_type,
							enum e_token_state s_token);
char					*single_quote_content(char *commande,
							t_token_list **token, enum e_token_type t_type,
							enum e_token_state s_token);
char					*double_quote_content(char *commande,
							t_token_list **token, enum e_token_type t_type,
							enum e_token_state s_token);
char					*get_out_redir_token(char *commande,
							t_token_list **token, enum e_token_type t_type,
							enum e_token_state s_token);
char					*get_in_redir_token(char *commande,
							t_token_list **token, enum e_token_type t_type,
							enum e_token_state s_token);
char					*dollar_geter(char *commande, t_token_list **token,
							enum e_token_type t_type,
							enum e_token_state s_token);
size_t					ft_strlen(const char *s);
char					*ft_strndup(char *to_dup, int len);

#endif