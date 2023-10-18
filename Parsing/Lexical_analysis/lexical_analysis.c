/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:38 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/16 18:19:23 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

/*should free the tokens selected to be joined*/
t_token_list	*lexical_analysis(char *commande, t_my_env **env)
{
	t_token_list	*token;
	char			*begin;
	
	begin = commande;
	token = NULL;
	while (commande && *commande)
		commande = lexems_finder(commande, &token);
	env_var_expansion(&token, env);
	tokens_cleaner(&token);
	free(begin);
	return (token);
}
