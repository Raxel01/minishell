#ifndef H_MINI_SHELL
# define H_MINI_SHELL

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct commande
{
    char *commande;
}   t_commande;

typedef struct details
{
    void *commande;
    void *option;

} t_data_details;

enum token_type
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
//SPECIAL_vAR IN SHELL LIKE : $1 $0..$?..$$.
enum token_state{
    NORMAL,
    IN_SQUOT,
    IN_DQUOT
};

typedef struct token_list
{
    char	*token;
    enum token_type type;
    enum token_state state;
    struct token_list *next;
    struct token_list *prev;
}       t_token_list;

typedef struct tree{
    void *data;
    enum token_state state;
    struct tree *left;
    struct tree *right;
}   t_trees;
 /*will may add messages option {}*/ 
 /****************EPUR_STRING : COMMANDE CLEANER ***********************/
 char *epur_string(char *commande);
 int epur_len_helper(char *commande);
 int word_epur_helper(char *commande);
/************************************************************************/
/*******************LINKED LIST FUNCTION*********************************/
t_token_list *build_new_token_node(char *token_data,\
        enum token_type type, enum token_state state);
void    add_tokens_to_list(t_token_list **token, \
        t_token_list *next_token);
/************************************************************************/
/*************************TOKENIZER =>TOOLS******************************/
void	lexical_analysis(char *commande);
char*   lexems_finder(char *commande, t_token_list **token);
int     Quoted_symbole(char c);
char*   get_t_word_token(char *commande, t_token_list **token,\
        enum token_type t_type, enum token_state s_token);
char*   get_space_token(char *commande, t_token_list **token, \
        enum token_type t_type, enum token_state s_token);
char*   get_pipe_token(char *commande, t_token_list **token, \
        enum token_type t_type, enum token_state s_token);
char*   single_quote_content(char *commande, t_token_list **token, \
        enum token_type t_type, enum token_state s_token);
char*   double_quote_content(char *commande, t_token_list **token, \
        enum token_type t_type, enum token_state s_token);
char*   get_out_redir_token(char *commande, t_token_list **token, \
        enum token_type t_type, enum token_state s_token);
char*   get_in_redir_token(char *commande, t_token_list **token, \
        enum token_type t_type, enum token_state s_token);
char*   dollar_geter(char *commande, t_token_list **token, \
        enum token_type t_type, enum token_state s_token);
char*   ft_strndup(char *to_dup, int len);
/************************************************************************/
#endif