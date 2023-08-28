#include "../Header/header.h"

// void    testing(char *commande)
// {
//     char *end = commande+ft_strlen(commande) -1;
//     char *begin = commande;
//     while (commande && *commande)
//     {
//         if (*commande == '\'' || *commande == '\"')
//         {
//             if (*commande == '\'')
//             {
//                 commande++;
//                 while (*commande != '\'')
//                     commande++;
//             }
//             else
//             {
//                 commande++;
//                 while (*commande != '\"')
//                 commande++;
//             }
//         }
//         if (*commande == ' ')
//            *commande = '#';
//        commande++;
//     }
// }

int digit_case(char c)
{
        return(c >= '0' && c <= '9');
}

int is_alphanum(char c)
{
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || digit_case(c));
}

int Quoted_symbole(char c)
{
	return ( c == '|' || c == '<'|| c ==  '>' || c == '$' || \
		 c == '"' || c == '\''|| c == ' ' || c == '\n'|| \
		 c == '\t');
}

int ft_isalpha(int c)
{
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
                return (1);
        else
                return (0);
}

static int ft_words(char const *s, char c)
{
        int i;
        int words;

        if (s[0] == '\0')
                return (0);
        words = 0;
        i = 0;
        while (s[i] == c) // doz delim
                i++;
        while (s[i])
        {
                if (s[i] == c && s[i - 1] != c)
                        words++;
                i++;
        }
        if (s[i - 1] != c)
                words++;
        return (words);
}

static char *next_word(char *str, char c, int *len)
{
        int i;
        char *tmp;
        int count;

        i = 0;
        count = 0;
        while (str[i] && str[i] == c)
                i++;
        tmp = &str[i];
        while (str[i] && str[i] != c)
        {
                count++;
                i++;
        }
        *len = count;
        return (tmp);
}

static char **ft_freetab(char **str, int tofree)
{
        while (--tofree >= 0)
                free(str[tofree]);
        free(str);
        str = NULL;
        return (str);
}

char **ft_split(char const *s, char c)
{
        int i;
        char **str;
        char *tmp;
        int words;
        int len;

        if (!s)
                return (NULL);
        i = -1;
        words = ft_words(s, c);
        str = (char **)malloc(sizeof(char *) * (words + 1));
        if (!str)
                return (NULL);
        tmp = (char *)s;
        len = 0;
        while (++i < words)
        {
                tmp = next_word(tmp + len, c, &len);
                str[i] = (char *)malloc(len + 1);
                if (!str[i])
                        return (ft_freetab(str, i));
                // strlcpy(str[i], tmp, len + 1);
        }
        str[i] = 0;
        return (str);
}

int ft_metacaracters(char input)
{
        char *meta;
        meta = " |&;()<>";
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

char *ft_strndup(char *to_dup, int len)
{
        if (to_dup && to_dup[0] != '\0')
        {
                int i;
                char *duped;
                
                i = 0;
                duped = malloc(sizeof(char) * (len + 1));
                if (!duped)
                        return (NULL);
                while (to_dup[i] && i < len)
                {
                        duped[i] = to_dup[i];
                        i++;
                }
                duped[i] = '\0';
                return (duped);
        }
        return (NULL);
}

char *epur_string(char *commande)
{
        int i;
        int flg = 0;
        char *epured_string = malloc(sizeof(char) * strlen(commande));
        char *begin = epured_string;
        i = 0;

        while (commande[i] && (commande[i] == ' ' || commande[i] == '\t'))
                ++i;
        while (commande[i])
        {
                if (commande[i] == ' ' || commande[i] == '\t')
                        flg = 1;
                if (!(commande[i] == ' ' || commande[i] == '\t'))
                {
                        if (flg)
                        {
                                *epured_string = ' ';
                                epured_string++;
                        }
                        flg = 0;
                        *epured_string = commande[i];
                        epured_string++;
                }
                i += 1;
        }
        *epured_string = '\0';

        return (begin);
}

size_t ft_strlen(const char *s)
{
        size_t i;

        i = 0;
        while (s[i])
                i++;
        return (i);
}

char *ft_strdup(const char *s)
{
        char *ptr;
        size_t len;
        size_t i;

        len = ft_strlen(s) + 1;
        i = 0;
        ptr = (char *)malloc(len * sizeof(char));
        if (!ptr)
                return (NULL);
        while (s[i])
        {
                ptr[i] = s[i];
                i++;
        }
        ptr[i] = '\0';
        return (ptr);
}

char *ft_substr(char const *s, size_t start, size_t len)
{
        char *str;
        unsigned int i; //i = 1; len = 11;
        unsigned int j;

        if (s)
        {
                i = start;
                j = 0;
                if (start >= ft_strlen(s))
                        return (ft_strdup(""));
                if (len >= ft_strlen(s))
                        len = ft_strlen(s);
                str = (char *)malloc(sizeof(char) * ((len - start) + 1));
                // printf("{state : %ld}\n", ((len - start) + 1));
                if (!str)
                        return (NULL);
                while (s[i] && i < len) // start = 5, len == 6 , start = len - 1; i < len + start
                {
                        // printf ("entred caracteres|%c|\n", s[i]);
                        str[j++] = s[i++];
                }
                str[j] = '\0';
                // printf("str : |%s|\n",str);
                return (str);
        }
        return (NULL);
}

int extract_special_token(char *commande, char search_for, int j, int *flag)
{
        if (search_for == '\'' || search_for == '\"')
        {
                *flag = 2;
                if (search_for == '\'')
                {
                        // i = j;
                        j++;
                        while (commande[j] != '\'')
                                j++;
                }
                else if (search_for == '\"')
                {
                        // i = j;
                        j++;
                        while (commande[j] != '\"')
                                j++;
                }
        }
        return (j);
}

int    check_symetric_metacaracters(char member, char next_member)
{
        if ( (member == '>' && next_member == '>') ||  (member == '<' && next_member == '<'))
                return (1);
        return (0);
}

// void Tokenizer(char *commande)
// {
//         int i = 0;
//         size_t j = 0;
//         int flag;
//         int s_quote;   
//         s_quote = 0;
//         while (j < ft_strlen(commande) && commande[j])
//         {
//                 flag = 0;
//                 i = j;
//                 j = extract_special_token(commande, commande[j], j, &s_quote);// cmd, cmd[0],0,
//                 while (j < ft_strlen(commande) && !ft_metacaracters(commande[j]))
//                 {
//                         flag = 1;
//                         ++j;
//                 }
//                 if (s_quote == 2)
//                 {
//                         i++;
//                         j -= 1 ;
//                 }
//                 if (flag)
//                         printf("%s\n", ft_substr(commande, i, j));
//                 if (j < ft_strlen(commande) && ft_metacaracters(commande[j]))
//                 {
//                         i = j;
//                         if (check_symetric_metacaracters(commande[j], commande[j+1]))
//                                 ++j;
//                         ++j;
//                         printf("%s\n", ft_substr(commande, i, j));
//                 }
//                 j--;
//                 j++;
//         }
// }

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
/*RE=CHECK THE LOGIC*/
char* get_pipe_token(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        int geter;

        geter = 0;
        while (commande[geter] && commande[geter] == '|')
                geter++;
        add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,geter), t_type, s_token));
        return (commande + geter); 
}

char* single_quote_content(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        int j;

        j = 0;
        commande++;
        while (commande[j] && commande[j] != '\'' )
                j++;
        if (j)
                add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,j), t_type, s_token));
        if (commande[j] == '\'')
                j++;
        return (commande + j);
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

int syntaxe_quote_checker(char *commande)
{
        int s_quote;
        int d_quote;

        s_quote = 0;
        d_quote = 0;
        while (commande && *commande)
        {
                if (*commande == '\'')
                        s_quote++;
                else if (*commande == '\"')
                        d_quote++;
                
                commande++;
        }
        if ((s_quote % 2 != 0) || (d_quote % 2 != 0))
                return (0);
        return (1);
}

/*RE=CHECK THE LOGIC*/
/*>>*/

char *get_out_redir_token(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        int geter;

        geter = 0;
        while (commande[geter] && commande[geter] == '>')
                geter++;
        add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,geter), t_type, s_token));
        return (commande + geter); 

}

/*RE=CHECK THE LOGIC*/
// <<
char *get_in_redir_token(char *commande, t_token_list **token, enum token_type t_type, enum token_state s_token)
{
        int geter;

        geter = 0;
        while (commande[geter] && commande[geter] == '<')
                geter++;
        add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,geter), t_type, s_token));
        return (commande + geter); 

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

void    print_tokens(t_token_list **begin)
{
    t_token_list *cursur;
    cursur = (*begin);
    while (cursur)
    {           //printf("-TOKEN_DATA\t----------------------------------------------------|\n");
                printf ("%s\t|\t%d\t|\t%d|\n", cursur->token, cursur->type, cursur->state);
                // printf("================================\n");
            cursur = cursur->next;
    }
}

void	lexical_analysis(char *commande)
{
	t_token_list *token;
        
        token = NULL;
        while (*commande)
                commande = lexems_finder(commande, &token);
        print_tokens(&token);
}

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
        free(commande.commande);
        return (0);
}