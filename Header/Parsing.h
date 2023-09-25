/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:14:30 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/22 21:44:16 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINISH_H
# define H_MINISH_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

#define ERROR_EXIT 2
#define SUCCES_PROC 0

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
	char	*env_var;
	char	*content;
}						t_env;

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
	APPEND_SYM,
	SYNTAX_ERROR,
	EXIT_STATUS,
};
enum					e_token_state
{
	NORMAL,
	IN_SQUOT,
	IN_DQUOT,
	Q_UNCLOSE,
	RED_ERR
};

typedef struct start_end_geter
{
	int					start;
	int					end;
	int					flag;
	int					node_member;
}						t_pos_get;

typedef struct token_list
{
	char				*token;
	enum e_token_type	type;
	enum e_token_state	state;
	int					index;
	int					node_member;
	struct token_list	*next;
	struct token_list	*prev;
}						t_token_list;
typedef struct v_envp
{
	char			*var;
	char			*var_content;
	char			**m_env;
	struct	v_envp 	*next;
	struct	v_envp 	*prev;
}	my_env;

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
t_token_list			*lexical_analysis(char *commande, my_env **env);
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
/**************************************TOKEN_CLEANER*********************/
void					tokens_cleaner(t_token_list **tokens);
char					*token_withoutquote(char *token,
							enum e_token_state state);
t_pos_get				*index_range_getter(t_token_list **tokens);
void					addclean_token(t_token_list **head, int start_index,
							int end_index, t_token_list *clean_node);
t_token_list			*data_assembler(t_token_list **tokens,
							t_pos_get *position);
void					specialcase_handler(t_token_list **tokens);
void					free_region(t_token_list **start, t_token_list **end);
/************************************************************************/
/******************************barkellah khellaaah**************************/
char					*ft_strjoin(char *s1, char *s2);
int						true_case_quote(char *to_search);
int						affect_index(t_token_list **token);
char					*assemble_data(t_token_list *begin, int end);
char					*extract_clean(char *token, int to_alloc, char c);
void					init_holder(t_pos_get **holder, t_token_list **tokens);
int						new_token_len(char *new_token,
							enum e_token_state state);
/***********************************************************************/
/*******************************SYNTAXE CHECK***************************/
int syntax_error(t_token_list *head);
/***********************************************************************/
/*********************************Environnement : envp******************/
void    env_var_expansion(t_token_list **tokens, my_env **env);
char    *ft_substr(char const *s, unsigned int start, size_t len);
int   	ft_strchr(char *s, char c);
my_env 	*build_member(char *env_member);
void    add_member(my_env **head_members, my_env *new_member);
my_env  *init_head(my_env **env_head, char ** sys_env);
my_env 	*import_env(char **sys_env);
int		ft_strcmp(char *s1, char *s2);
void    free_env(my_env **env);
void    print_env(my_env **env);
/***********************************************************************/
#endif