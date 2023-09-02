#include "../Header/header.h"

int Quoted_symbole(char c)
{
	return ( c == '|' || c == '<'|| c ==  '>' || c == '$' || \
		 c == '"' || c == '\''|| c == ' ' || c == '\n'|| \
		 c == '\t');
}

char* get_t_word_token(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        int j;

        j = 0;
        while (commande[j] && !Quoted_symbole(commande[j]))
                j++;
        add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,j), t_type, s_token));
        return (commande + j);
}

char* get_space_token(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,1), t_type, s_token));
        return (commande + 1);
}

char* get_pipe_token(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,1), t_type, s_token));
        return (commande +1); 
}

char*  lexems_finder(char *commande, t_token_list **token)
{
        if (!Quoted_symbole(*commande))
                commande = get_t_word_token(commande, token, WORD, NORMAL);
        else if (*commande == ' ')
                commande = get_space_token(commande, token,A_SPACE, NORMAL);
        else if (*commande == '|')
                commande = get_pipe_token(commande, token,PIPE, NORMAL);
        else if (*commande == '\'')
                commande = single_quote_content(commande,token, WORD, IN_SQUOT);
        else if (*commande == '\"')
                commande = double_quote_content(commande,token, WORD, IN_DQUOT);
        else if (*commande == '>')
                commande = get_out_redir_token(commande,token, OUT_REDIR, NORMAL);
        else if (*commande == '<')
                commande = get_in_redir_token(commande,token, IN_REDIR, NORMAL);
        else if (*commande == '$')
                commande = dollar_geter(commande,token, ENV_VAR, NORMAL);
        return (commande);
}