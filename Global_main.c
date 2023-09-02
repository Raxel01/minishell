#include "./Header/header.h"

int main()
{
        t_commande commande;
        while (1)
        {
                commande.commande = readline("MINISHELL[~] -> ");
                if (commande.commande == NULL)
                        return (0);
                commande.commande = epur_string(commande.commande);
                lexical_analysis(commande.commande);
        }
        // free(commande.commande);
        return (0);
}