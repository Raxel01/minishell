/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_sequel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:54 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/25 22:22:28 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int	digit_case(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_alphanum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || digit_case(c));
}
/*return (commande + J + 1) because $ is not inclu in j calculated*/
char	*dollar_geter(char *commande, t_token_list **token, enum e_token_type t_type, enum e_token_state s_token)
{
	int	j;

	j = 0;
	if (*(commande + 1) && (digit_case(*(commande + 1)) || *(commande
				+ 1) == '?' || *(commande + 1) == '$'))
	{
		if (*(commande + 1) == '?')
			t_type = EXIT_STATUS;
		else
			t_type = SPECIAL_VAR;
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande, 2),
				t_type, s_token));
		return (commande + 2);
	}
	while (commande[j + 1] && (is_alphanum(commande[j + 1]) || commande[j
			+ 1] == '_'))
		j++;
	if (!j)
		t_type = WORD;
	if (j)
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande, j
					+ 1), t_type, s_token));
	else
	{
		if (commande[j + 1])
			j++;
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande, j
					+ 1), t_type, s_token));
	}
	return (commande + j + 1);
}

int	extract_dquot_content(char **commande, t_token_list **token, enum e_token_type t_type, enum e_token_state s_token)
{
	int j;
	
	j = 0;
	while ((*commande)[j] && (*commande)[j] != '\"')
	{
		if ((*commande)[j] == '$')
		{
			if (j)
				add_tokens_to_list(token, \
					build_new_token_node(ft_strndup((*commande), j), t_type, s_token));
			(*commande) = dollar_geter((*commande) + j, token, ENV_VAR, s_token);
			j = 0;
		}
		else
		{
			if ((*commande)[j + 1] == '\"' && (*commande)[j + 2] == '\"')
				j += 2;
			j++;
		}
	}
	return (j);
}

char	*double_quote_content(char *commande, t_token_list **token, enum e_token_type t_type, enum e_token_state s_token)
{
	int	j;

	commande++;
	j = extract_dquot_content(&commande, token, t_type, s_token);
	if (commande[j] == 0 || !(*commande))
	{
		t_type = SYNTAX_ERROR;
		s_token = Q_UNCLOSE;
		if (*commande == commande[j])
		{
			add_tokens_to_list(token, build_new_token_node(ft_strndup("SYNTAXE_ERROR", \
				ft_strlen("SYNTAXE_ERROR")), t_type, s_token));
			return (commande + j);
		}
	}
	if (j)
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande, j), t_type, s_token));
	if (commande[j] == '\"')
		j++;
	return (commande + j);
}
