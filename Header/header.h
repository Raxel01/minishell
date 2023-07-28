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
enum token_type
{
    word,
    operator,
    me,
    in
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