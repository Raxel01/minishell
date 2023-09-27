/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:38 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/27 21:59:11 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

const char		*token_content[] = {"WORD", "A_SPACE", "PIPE", "OUT_REDIR",
			"IN_REDIR", "ENV_VAR", "SPECIAL_VAR", "HERE_DOC", "APPEND_SYM",
			"SYNTAX_ERROR", "EXIT_STATUS"};

const char		*token_state[] = {"NORMAL", "IN_SQUOT", "IN_DQUOT", "Q_UNCLOSE",
			"RED_ERR"};

// int	syntaxe_quote_checker(char *commande)
// {
// 	int	s_quote;
// 	int	d_quote;
// 	s_quote = 0;
// 	d_quote = 0;
// 	while (commande && *commande)
// 	{
// 		if (*commande == '\'')
// 			s_quote++;
// 		else if (*commande == '\"')
// 			d_quote++;
// 		commande++;
// 	}
// 	if ((s_quote % 2 != 0) || (d_quote % 2 != 0))
// 		return (0);
// 	return (1);
// }

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

/*should free the tokens selected to be joined*/
t_token_list	*lexical_analysis(char *commande, t_my_env **env)
{
	t_token_list	*token;

	(void)env;
	token = NULL;
	while (commande && *commande)
		commande = lexems_finder(commande, &token);
	env_var_expansion(&token, env);
	tokens_cleaner(&token);
	return (token);
}
