#ifndef MINI_SHELL
# define MINI_SHELL

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
    A_SPACE = ' ',
    PIPE = '|',
    OUT_REDIR = '>',
    IN_REDIR = '<',
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
 //will may add messages option {} 
/*******************LINKED LIST FUNCTION*********************************/
t_token_list *build_new_token_node(char *token_data,\
            enum token_type type, enum token_state state);
void    add_tokens_to_list(t_token_list **token, \
            t_token_list *next_token);
/************************************************************************/

/*************************TOKENIZER UTILS********************************/
void	lexical_analysis(char *commande);
/************************************************************************/
#endif