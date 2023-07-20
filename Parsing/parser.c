#include "../Header/header.h"
#include   <string.h>

int main (int ac, char **av)
{
    // make a binnary tree thta store a tree of a family 
    t_commande commande;
    t_trees *Root;
    Root = malloc(sizeof(t_trees));
    while (1)
    {
        commande.commande = readline("MINISHELL dzeb ->");
        if (commande.commande == NULL)
            {

            printf("\n");
            return (0);
            }
        Root->data = commande.commande;
        // printf("|%s |\n", Root->data);
    }

    
    // t_trees *left_child;
    
    // t_trees *right_child;
    
    // left_child = malloc(sizeof(t_trees));
    // left_child->data = av[1];
    // left_child->left = NULL;
    // left_child->right = NULL;
    
    // right_child = malloc(sizeof(t_trees));
    // right_child->data = av[2];
    // right_child->left = NULL;
    // right_child->right = NULL;
    
    // Root->left = left_child;
    // Root->right = right_child;
    // printf("the ROOT = %s |\n Left : %s| \n right : %s|\n", Root->data, Root->left->data, Root->right->data);
    return (0);
}