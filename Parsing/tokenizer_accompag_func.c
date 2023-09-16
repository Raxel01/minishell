/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_accompag_func.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:51 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/15 19:23:44 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing_Header.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(char *to_dup, int len)
{
	int		i;
	char	*duped;

	if (to_dup && to_dup[0] != '\0')
	{
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
		// free(to_dup);
		return (duped);
	}
	return (NULL);
}
/*the LAST CONDITION IS ABOUT SKIPPING THE '\'' IF THE BOUCLE WAS STOPED BY IT*/
char	*single_quote_content(char *commande, t_token_list **token,
		enum e_token_type t_type, enum e_token_state s_token)
{
	int	j;

	j = 0;
	commande++;
	while (commande[j] && commande[j] != '\'')
	{
		if (commande[j + 1] == '\'' && commande[j+2] == '\'')
			j+=2;
		j++;
	}
	if (j)
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande, j),
				t_type, s_token));
	if (commande[j] == '\'')
		j++;
	return (commande + j);
}

/*>>*/
char	*get_out_redir_token(char *commande, t_token_list **token,
		enum e_token_type t_type, enum e_token_state s_token)
{
	int	geter;

	geter = 1;
	while (commande[geter] && commande[geter] == '>')
		geter++;
	if (geter == 2)
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,
					geter), APPEND_SYM, s_token));
	else if(geter == 1)
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,
					geter), t_type, s_token));
	else
			add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,
					geter), WORD, s_token));
	return (commande + geter);
}

/*<<*/
char	*get_in_redir_token(char *commande, t_token_list **token,
		enum e_token_type t_type, enum e_token_state s_token)
{
	int	geter;

	geter = 1;
	while (commande[geter] && commande[geter] == '<')
		geter++;
	if (geter == 2)
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,
					geter), HERE_DOC, s_token));
	else if(geter == 1)
		add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,
					geter), t_type, s_token));
	else
			add_tokens_to_list(token, build_new_token_node(ft_strndup(commande,
					geter), WORD, s_token));
	return (commande + geter);
}
