/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:38 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/08 20:33:09 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing_Header.h"

const char *token_content[] = {
    "WORD",
    "A_SPACE",
    "PIPE",
    "OUT_REDIR",
    "IN_REDIR",
    "ENV_VAR",
    "SPECIAL_VAR",
    "HERE_DOC",
    "APPEND_SYM"
};

const char *token_state[] = {
    "NORMAL",
    "IN_SQUOT",
    "IN_DQUOT",
};

int	syntaxe_quote_checker(char *commande)
{
	int	s_quote;
	int	d_quote;

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

/*char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc(len_s1 + len_s2 + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < len_s1)
		join[i] = s1[i];
	while (j < len_s2)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}*/

void    print_tokens(t_token_list **begin)
{
    t_token_list *cursur;
    cursur = (*begin);
    printf("*******************************************************************\n");
    printf("*        TOKENS         |       TOKEN TYPE      |   TOKEN STATE   *\n");
    printf("*******************************************************************\n");
    while (cursur)
    {
        printf ("*%-20s\t|\t%-10s\t|\t%-10s*\n", cursur->token, token_content[cursur->type], token_state[cursur->state]);
    printf("*******************************************************************\n");
            cursur = cursur->next;
    }
}

void	lexical_analysis(char *commande)
{
	t_token_list	*token;

	token = NULL;
	while (*commande)
		commande = lexems_finder(commande, &token);
	print_tokens(&token);
}
