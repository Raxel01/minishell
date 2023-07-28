#include "../Header/header.h"
#include   <string.h>

int metacaracters(char input)
{
    char *meta;
    // meta = malloc(sizeof(char) * 8);
    meta = "    |&;()<>";
    int i;

    i = 0;
    while (meta[i])
    {
        if (meta[i] == input)
            return (1);
        i++;
    }
return (0);
}

void    Lexical_analysis(char *data)
{
    char *input;
    input = data;
    char *stoped;
    int flag = 0;

    while (*input)
    {
        if ((*input) != '\'')
            write(1, input, 1);
        input++;
    }
    write(1, "\n", 1);
}
void    get_content_single_quotes(char *commande)
{
    if (single_quotes contant >)
    while ((*commande) && *(commande) != '\'')
        commande++;
    if(*commande && (*commande) == '\'')
        commande++;
    while ((*commande) && (*commande) != '\'')
    {
        write(1, commande,1);
        commande++;
    }
    write(1, "  ", 1);
}
int main (int ac, char **av)
{
    // make a binnary tree that store a tree of a family 
    t_commande commande;
    // enum tokens tokeen;

    // t_trees *Root;
    // Root = malloc(sizeof(t_trees));
    while (1)
    {
        commande.commande = readline("MINISHELL[~] ->");
        if (commande.commande == NULL)
            return (0);
        get_content_single_quotes(commande.commande);
    }
    return (0);
}