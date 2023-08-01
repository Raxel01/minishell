#ifndef MINI_SHELL
# define MINI_SHELL

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
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
/*O : mean OPEN*/
/*C: CLOSE*/
enum token_type
{
    WORD,
    SPACE = ' ',
    O_PARE = '(',
    C_PARE = ')',
    PIPE = '|',
    OUT_REDIR = '>',
    INT_REDIR = '<',
    O_SINGLE_QUOT = '\'',
    C_SIGLE_QUOT = '\'',
    O_DOUBLE_QUOT = '\"',
    C_DOUBLE_QUOT = '\"',
    HERE_DOC = '<<',
    APPEND_SYM = '>>'
    O_BRAKETS = '{',
    C_BRAKETS = '}'
};

typedef struct token_list
{
    void *content;
    enum token_type data_type;
    struct token_list *next;
    struct token_list *prev;
}       t_token_list;


typedef struct tree{
    void *data;
    struct tree *left;
    struct tree *right;
}   t_trees;

#endif