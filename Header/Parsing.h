/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:10:20 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/27 22:25:13 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINISH_H
# define H_MINISH_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERROR_EXIT 2
# define SUCCES_PROC 0
# define NOT_VALID 1

# define SYNTAXE_ERR_STATUS 2
# define M_APPEND 13
# define M_ECRASE 37

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
	char				*var;
	char				*var_content;
	char				**m_env;
	struct v_envp		*next;
	struct v_envp		*prev;
}						t_my_env;

enum					e_type
{
	NONE,
	CMD,
	OPTION,
	FD_FILE,
};

enum					e_file_type
{
	NONEF,
	OUTFILE,
	INFILE,
	APPEND,
	HEREDOC_LIM,
};

typedef struct cmd
{
	char				*content;
	enum e_type			category;
	enum e_file_type	file;
	enum e_token_type	type;
	enum e_token_state	state;
	struct cmd			*next;
	struct cmd			*prev;
}						t_cmd;

typedef struct l_cmd
{
	char				**cmd_table;
	int					in_fd;
	int					out_fd;
	struct l_cmd		*next;
	struct l_cmd		*prev;
}						t_cmd_table;

typedef struct in_out
{
	int					in_fd;
	int					out_fd;
}						t_in_out;

enum					e_heredoc
{
	STRING,
	VAR,
};
typedef struct here_d
{
	char				*data;
	enum e_heredoc		type;
	struct here_d		*next;

}						t_here_doc;

typedef struct export
{
	char				*elem_name;
	char				*elem_value;
	int					mode;
}
t_export;
/*will may add messages option {}*/
/***************************GLOBAL_OUTFUNCTION*****************************/
void					white_space(char *str, size_t i, size_t len,
							int *state);
void					clean_memory(t_token_list **token);
/**************************************************************************/
/****************EPUR_STRING : COMMANDE CLEANER :[3]***********************/
char					*epur_string(char *commande);
int						epur_len_helper(char *commande);
int						word_epur_helper(char *commande);
/************************************************************************/
/*******************LINKED LIST FUNCTION:[4]*********************************/
t_token_list			*build_new_token_node(char *token_data,
							enum e_token_type type, enum e_token_state state);
void					add_tokens_to_list(t_token_list **token,
							t_token_list *next_token);
void					print_tokens(t_token_list **begin);
void					free_token_list(t_token_list **head);
/************************************************************************/
/*************************TOKENIZER =>TOOLS:[13]******************************/
t_token_list			*lexical_analysis(char *commande, t_my_env **env);
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
int						set_j(char *command, int j);
int						var_extracter(char *commande, int j);
char					*get_out_redir_token(char *commande,
							t_token_list **token, enum e_token_type t_type,
							enum e_token_state s_token);
char					*get_in_redir_token(char *commande,
							t_token_list **token, enum e_token_type t_type,
							enum e_token_state s_token);
char					*dollar_geter(char *commande, t_token_list **token,
							enum e_token_type t_type,
							enum e_token_state s_token);
enum e_token_type		type_is(char c);
char					*home_geter(char *commande, t_token_list **token,
							enum e_token_type t_type,
							enum e_token_state s_token);
int						var_extracter(char *commande, int j);
size_t					ft_strlen(const char *s);
char					*ft_strndup(char *to_dup, int len);
int						is_alphanum(char c);
/**************************************TOKEN_CLEANER:[7]*********************/
void					tokens_cleaner(t_token_list **tokens);
char					*token_withoutquote(char *token,
							enum e_token_state state);
t_pos_get				*index_range_getter(t_token_list **tokens);
int						true_state(t_token_list *current);
void					addclean_token(t_token_list **head, int start_index,
							int end_index, t_token_list *clean_node);
t_token_list			*data_assembler(t_token_list **tokens,
							t_pos_get *position);
void					specialcase_handler(t_token_list **tokens);
void					free_region(t_token_list **start, t_token_list **end);
/************************************************************************/
/******************************barkellah khellaaah:[7]*******************/
char					*ft_strjoin(char *s1, char *s2);
int						true_case_quote(char *to_search);
int						affect_index(t_token_list **token);
char					*assemble_data(t_token_list *begin, int end);
char					*extract_clean(char *token, int to_alloc, char c);
void					init_holder(t_pos_get **holder, t_token_list **tokens);
int						new_token_len(char *new_token,
							enum e_token_state state);
/***********************************************************************/
/*******************************SYNTAXE CHECK:[8]***************************/
int						syntax_analysis(t_token_list *head);
void					error_type(t_token_list *cursur);
int						redir_case(enum e_token_type type);
int						redir_analyser(t_token_list *cursur);
void					error_announcer(char *error, int syntax);
int						pipe_analyser(t_token_list *cursus);
int						is_outred(t_token_list *behind, t_token_list *forward);
t_token_list			*behind_getter(t_token_list *cursus);
t_token_list			*forward_getter(t_token_list *cursus);
/***********************************************************************/
/*********************************Environnement : envp : [10]******************/
void					env_var_expansion(t_token_list **tokens,
							t_my_env **env);
char					*replaceby_content(char *search_for, t_my_env **env);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						ft_strchr(char *s, char c);
t_my_env				*build_member(char *env_member);
void					add_member(t_my_env **head_members,
							t_my_env *new_member);
t_my_env				*init_head(t_my_env **env_head, char **sys_env);
t_my_env				*import_env(char **sys_env);
int						ft_strcmp(char *s1, char *s2);
void					free_env(t_my_env **env);
void					print_env(t_my_env **env);
/***********************************************************************/
/******************************SEND_DATA*[14]*******************************/
t_cmd_table				*parsing(t_token_list **tokens);
void					printcmd_list(t_cmd **cmd);
void					addto_list(t_cmd **cmd, t_cmd *next_data);
t_cmd					*build_node(char *data, enum e_token_type intype,
							enum e_token_state in_state);
void					redir_cleaner(t_cmd **head);
void					commande_recognizer(t_cmd **cmd);
void					redirect_recognizer(t_cmd **cmd);
void					options_recognizer(t_cmd **cmd);
void					grammar_adapter(t_cmd **cmd);
void					free_cmd(t_cmd **cmd);
/***********************************************************************/
/*************************Build_Last_list*******************************/
int						arg_count(t_cmd **head);
int						infile_size(t_cmd **head);
int						outfile_getter(t_cmd **head);
int						append_size(t_cmd **head);
int						heredoc_size(t_cmd **head);
t_cmd_table				*build_commandtable_node(t_cmd **head);
void					addto_listt(t_cmd_table **cmd, t_cmd_table *next_data);
void					print_cmd_table(t_cmd_table **cmd_tab);
t_in_out				process_fd(t_cmd **head);
void					cmd_table_builder(t_cmd_table **cmd_table,
							t_cmd **head);
t_cmd					*head_cursur(t_cmd *head);
void					free_cmd_table(t_cmd_table **cmd);
/***********************************************************************/
/*******************************BUILT_IN*********************************/
int						builtin_recognizer(t_cmd_table **head, char **cmd_table,
							t_my_env **env);
int						run_cd(char **cmd_table, t_my_env **env);
int						run_pwd(char **cmd_table);
int						run_env(char **cmd_tabl, t_my_env **env);
int						run_echo(char **cmd_table);
int						run_exit(t_cmd_table **head, char **cmd_table,
							t_my_env **env);
int						run_unset(char **cmd_table, t_my_env **env);
int						bashvar_norm(char *var);
int						is_alpha(char c);
int						run_export(char **cmd_table, t_my_env **env);
/************************************************************************/
/******************************EXPORT : UTILS****************************/
t_my_env				*duplicate_env(t_my_env **original);
t_my_env				*creatdup(char *var, char *var_content);
void					sorting(t_my_env *env);
char					*ft_strdup(char *s);
void					regulateur(t_my_env *curs, t_my_env *next);
void					addenvmember(t_export e, t_my_env **env);
short					search(char *elem, t_my_env **env);
void					appendmode(t_export e, t_my_env **env);
void					ecrasmode(t_export e, t_my_env **env);
void					modifyenv(t_export e, t_my_env **env);
/************************************************************************/
/********************************HERE_DOC_FUNCTION***********************/
t_here_doc				*creatnodes(char *content, enum e_heredoc h_type);
void					list_builder(t_here_doc **head, t_here_doc *new_node);
char					*get_string(char *readed_data, enum e_heredoc type,
							t_here_doc **head);
char					*get_var(char *readed_data, enum e_heredoc type,
							t_here_doc **head);
int						digit_case(char c);
char					*extract_elems(char *readed_data, t_here_doc **head);
char					*data_expander(char *readed_data, t_my_env **env);
int						here_doc_(char *eof, enum e_token_state state,
							t_my_env **env);
void					elem_expansion(t_here_doc **head, t_my_env **env);
void					free_herelist(t_here_doc **head);
char					*concatenate_data(t_here_doc **head);
/************************************************************************/
/*************************STATUS_setter**********************************/
int						status_setter(int code, int mode);
char					*ft_itoa(int n);
int						nb_isdigit(int n);
int						get_is_negative(int n);
char					*strrev(char *str);
long					ft_abs(long n);
void					*ft_calloc(size_t count, size_t size);
/************************************************************************/
#endif