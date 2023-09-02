#include "../Header/header.h"

int digit_case(char c)
{
        return(c >= '0' && c <= '9');
}

int is_alphanum(char c)
{
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || digit_case(c));
}

char* dollar_geter(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        int j;

        if(digit_case(*(commande + 1)) || \
                *(commande + 1) == '?' || *(commande+1) == '$')
                {
                add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,2), \
                        SPECIAL_VAR, s_token));
                        return (commande + 2);
                }
        j = 0;
                while (commande[j+1] && (is_alphanum(commande[j+1]) || commande[j+1] == '_'))
                        j++;
        if (j)
                add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,j + 1), \
                        t_type, s_token));
        else
        {
                j++;
                add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,j + 1), \
                        t_type, s_token));
        }
        return (commande + j + 1);
}

char*   double_quote_content(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        int j;
        j = 0;
        commande++;
        while (commande[j] && commande[j] != '\"' )
        {
                if (commande[j] == '$')
                {
                        if (j)
                                 add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,j), t_type, s_token));
                        commande = dollar_geter(commande + j, token,ENV_VAR,s_token);
                        j = 0;
                }
                else
                        j++;
        }
        if (j)
                add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,j), t_type, s_token));
        if (commande[j] == '\"')
                j++;
        return (commande + j);
}