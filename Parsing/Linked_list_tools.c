#include "../Header/header.h"

// t_token_list *init_head(t_token_list **node)
// {
//     *node = malloc(sizeof(t_token_list));
//     (*node)->prev= NULL;
//     (*node)->token = "Brahim";
//     (*node)->next= NULL;
//     return (*node);
// }

t_token_list *build_new_token_node(char *token_data, enum token_type type, enum token_state state)
{
    t_token_list *token;

    token = malloc(sizeof(t_token_list));
    token->token = token_data;
    token->type = type;
    token->state = state;
    token->next = NULL;
    token->prev = NULL;
    return (token);
}

void    add_tokens_to_list(t_token_list **token, t_token_list *next_token)
{
    t_token_list *cursur;
    
    if (!(*token))
        (*token) = next_token;
    else
    {
        cursur = *token;
        while (cursur->next)
            cursur = cursur->next;
        cursur->next = next_token;
        next_token->prev = cursur;
    }
}
