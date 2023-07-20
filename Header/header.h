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

typedef struct tree{
    void *data;
    struct tree *left;
    struct tree *right;
} t_trees;

#endif