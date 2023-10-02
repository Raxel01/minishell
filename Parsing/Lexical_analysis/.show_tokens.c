/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .show_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:21:53 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/01 22:29:22 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

const char *token_content[] = {"WORD", "A_SPACE", 
	"PIPE", "OUT_REDIR",
			"IN_REDIR", "ENV_VAR", 
"SPECIAL_VAR", "HERE_DOC", "APPEND_SYM",
			"SYNTAX_ERROR", "EXIT_STATUS"};

const char *token_state[] = {"NORMAL", "IN_SQUOT",
 "IN_DQUOT", "Q_UNCLOSE",
			"RED_ERR"};

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

void	print_tokens(t_token_list **begin)
{
	t_token_list	*cursur;

	if (!(*begin))
		return ;
	cursur = (*begin);
	printf("*******************************************************************\n");
	printf("*        TOKENS         |       TOKEN TYPE      |   TOKEN STATE   *\n");
	printf("*******************************************************************\n");
	while (cursur)
	{
		printf("*%-20s\t|\t%-10s\t|\t%-10s*\n", cursur->token,
			token_content[cursur->type], token_state[cursur->state]);
		printf("*******************************************************************\n");
		cursur = cursur->next;
	}
}

void    printcmd_list(t_cmd **cmd)
{
    t_cmd *cursur;

    cursur = (*cmd);
    printf("*******************************************************************\n");
	printf("*        CONTENT         |          TYPE         |       STATE    *\n");
	printf("*******************************************************************\n");
    while (cursur)
    {                                                            
        printf("*%-20s\t|\t%-10s\t|\t%-10s*\n", cursur->content,
			token_content[cursur->type], token_state[cursur->state]);
		printf("*******************************************************************\n");
        cursur = cursur->next;
    }
}
